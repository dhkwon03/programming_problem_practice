import numpy as np
import matplotlib.pyplot as plt
import tensorflow as tf
import pandas as pd
import re
import urllib.request
import time
import tensorflow_datasets as tfds

class PositionalEncoding(tf.keras.layers.Layer):
    def __init__(self, position, d_model):
        super(PositionalEncoding, self).__init__()
        self.pos_encoding = self.positional_encoding(position, d_model)


    def get_angles(self, position, i, d_model):
        angles = 1 / tf.pow(10000, (2*(i//2)) / tf.cast(d_model, tf.float32))
        return position * angles

    def positional_encoding(self, position, d_model):
        angle_rads = self.get_angles(position=tf.range(position, dtype=tf.float32)[:, tf.newaxis], 
                i=tf.range(d_model, dtype=tf.float32)[tf.newaxis, :],
                d_model=d_model)

        # for even index of the array, apply sine function
        sines = tf.math.sin(angle_rads[:, 0::2])

        # for odd index of the array, apply cosine function
        cosines = tf.math.cos(angle_rads[:, 1::2])

        angle_rads = np.zeros(angle_rads.shape)
        angle_rads[:, 0::2] = sines
        angle_rads[:, 1::2] = cosines
        pos_encoding = tf.constant(angle_rads)
        pos_encoding = pos_encoding[tf.newaxis, ...]

        # print position encoding result dimension
        print(pos_encoding.shape)
        return tf.cast(pos_encoding, tf.float32)

    def call(self, inputs):
        return inputs + self.pos_encoding[:, :tf.shape(inputs)[1], :]

class MultiHeadAttention(tf.keras.layers.Layer):
    def __init__(self, d_model, num_heads, name="multi_head_attention"):
        super(MultiHeadAttention, self).__init__(name=name)
        self.num_heads = num_heads
        self.d_model = d_model

        assert d_model % self.num_heads == 0

        self.depth = d_model // self.num_heads  # depth = 64 in paper

        self.query_dense = tf.keras.layers.Dense(units=d_model)
        self.key_dense = tf.keras.layers.Dense(units=d_model)
        self.value_dense = tf.keras.layers.Dense(units=d_model)

        self.dense = tf.keras.layers.Dense(units=d_model)

    # split Q, K, and V to the number of num_heads
    def split_heads(self, inputs, batch_size):
        inputs = tf.reshape(inputs, shape=(batch_size, -1, self.num_heads, self.depth))
        return tf.transpose(inputs, perm=[0,2,1,3])

    def call(self, inputs):
        query, key, value, mask = inputs['query'], inputs['key'], inputs['value'], inputs['mask']
        batch_size = tf.shape(query)[0]

        # step 1 : pass through dense layer of WQ, WK, WV
        # Q : batch_size * query's sentence length * d_model
        # K : batch_size * key's sentence length * d_model
        # V : batch_size * value's sentence length * d_model

        query = self.query_dense(query)
        key = self.key_dense(key)
        value = self.value_dense(value)

        # step 2 : divide heads
        # Q : batch_size * num_heads * query's sentence length * d_model/num_heads
        # K : batch_size * num_heads * key's sentence length * d_model/num_heads
        # V : batch_size * num_heads * value's sentence length * d_model/num_heads

        query = self.split_heads(query, batch_size)
        key = self.split_heads(key, batch_size)
        value = self.split_heads(value, batch_size)

        # step 3 : scale dot product attention
        # scaled attention : batch_size * num_heads * query's sentence length * d_model/num_heads
        scaled_attention, _ = scaled_dot_product_attention(query, key, value, mask)
        # transpose of scaled attention : batch_size * query's sentence length * num_heads * d_model/num_heads
        scaled_attention = tf.transpose(scaled_attention, perm=[0,2,1,3])

        # step 4 : concatenate heads
        # concate attention : batch_size * query's sentence length * d_model
        concat_attention = tf.reshape(scaled_attention, (batch_size, -1, self.d_model))

        # step 5 : pass through dense layer of WO
        # outputs : batch_size * query's sentence length * d_model
        outputs = self.dense(concat_attention)

        return outputs


def create_padding_mask(x):
    mask = tf.cast(tf.math.equal(x, 0), tf.float32)
    return mask[:, tf.newaxis, tf.newaxis, :]

def scaled_dot_product_attention(query, key, value, mask):
    # query : batch_size * num_heads * query sentence length * d_model/num_heads
    # key : batch_size * num_heads * key sentence length * d_model/num_heads
    # value : batch_size * num_heads * value sentence length * d_model/num_heads
    # padding_mask : batch_size * 1 * 1 * key sentence length

    # Q * K matrix multiplication
    matmul_qk = tf.matmul(query, key, transpose_b=True)

    # scaling (divide with dimension of k (d_k))
    depth = tf.cast(tf.shape(key)[-1], tf.float32)
    logits = matmul_qk / tf.math.sqrt(depth)

    # masking (put very small magnitude negative value to masking area)
    # very small magnitude value becomes 0 after softmax function
    if mask is not None:
        logits += (mask * -1e9)

    # softmax function
    # applying axis of softmax function is last dimension; key's sentence
    # attention weight : batch_size * num_heads * query sentence length * key sentence length
    attention_weights = tf.nn.softmax(logits, axis=-1)

    # output : batch_size * num_heads * query sentence length * d_model/num_heads
    output = tf.matmul(attention_weights, value)

    return output, attention_weights

def encoder_layer(dff, d_model, num_heads, dropout, name="encoder_layer"):
    inputs = tf.keras.Input(shape=(None, d_model), name="inputs")

    # use padding mask for encoder
    padding_mask = tf.keras.Input(shape=(1,1,None), name="padding_mask")

    # multi-head attention
    # 1st sub-layer; self-attention
    attention = MultiHeadAttention(d_model, num_heads, name="attention")({'query': inputs, 'key': inputs, 'value': inputs, 'mask': padding_mask})

    # Dropout & residual connection & layer normalization
    attention = tf.keras.layers.Dropout(rate=dropout)(attention)
    attention = tf.keras.layers.LayerNormalization(epsilon=1e-6)(inputs + attention)


    # position wise Feed Forward NN (2nd sub-layer)
    outputs = tf.keras.layers.Dense(units=dff, activation='relu')(attention)
    outputs = tf.keras.layers.Dense(units=d_model)(outputs)

    # Dropout & residual connection & layer normalization
    outputs = tf.keras.layers.Dropout(rate=dropout)(outputs)
    outputs = tf.keras.layers.LayerNormalization(epsilon=1e-6)(attention + outputs)

    return tf.keras.Model(inputs=[inputs, padding_mask], outputs=outputs, name=name)

def encoder(vocab_size, num_layers, dff, d_model, num_heads, dropout, name="encoder"):
    inputs = tf.keras.Input(shape=(None,), name="inputs")

    padding_mask = tf.keras.Input(shape=(1,1,None), name="padding_mask")

    # embedding -> positional encoding -> dropout
    embeddings = tf.keras.layers.Embedding(vocab_size, d_model)(inputs)
    embeddings *= tf.math.sqrt(tf.cast(d_model, tf.float32))
    embedding = PositionalEncoding(vocab_size, d_model)(embeddings)
    outputs = tf.keras.layers.Dropout(rate=dropout)(embeddings)

    # stack encoder by the number of num_layers
    for i in range(num_layers):
        outputs = encoder_layer(dff=dff, d_model=d_model, num_heads=num_heads, dropout=dropout, name="encoder_layer_{}".format(i))([outputs, padding_mask])

    return tf.keras.Model(inputs=[inputs, padding_mask], outputs=outputs, name=name)


# masking the future token on the 1st sub-layer of decoder
def create_look_ahead_mask(x):
    seq_len = tf.shape(x)[1]
    look_ahead_mask = 1 - tf.linalg.band_part(tf.ones((seq_len, seq_len)), -1, 0)
    # cf.) band_part(ones, negative, 0) --> create lower triangle matrix with ones matrix
    padding_mask = create_padding_mask(x)
    # include both look_ahead_mask and padding_mask
    return tf.maximum(look_ahead_mask, padding_mask)

def decoder_layer(dff, d_model, num_heads, dropout, name="decoder_layer"):
    inputs = tf.keras.Input(shape=(None, d_model), name="inputs")
    enc_outputs = tf.keras.Input(shape=(None, d_model), name="encoder_outputs")

    # look ahead mask (1st sub-layer)
    look_ahead_mask = tf.keras.Input(shape=(1,None,None), name="look_ahead_mask")

    # multi-head attention (1st sub-layer; masked self-attention)
    attention1 = MultiHeadAttention(d_model, num_heads, name="attention_1")(inputs={'query': inputs, 'key': inputs, 'value': inputs, 'mask': look_ahead_mask})

    # residual connection & layer normalization
    attention1 = tf.keras.layers.LayerNormalization(epsilon=1e-6)(attention1 + inputs)

    # padding mask (2nd sub-layer)
    padding_mask = tf.keras.Input(shape=(1,1,None), name='padding_mask')
    
    # multi-head attention (2nd sub-layer; decoder-encoder attention)
    attention2 = MultiHeadAttention(d_model, num_heads, name="attention_2")(inputs={'query':attention1, 'key': enc_outputs, 'value': enc_outputs, 'mask': padding_mask})

    # dropout & residual connnection & layer normalization
    attention2 = tf.keras.layers.Dropout(rate=dropout)(attention2)
    attention2 = tf.keras.layers.LayerNormalization(epsilon=1e-6)(attention2 + attention1)

    # position wise Feed Forward NN (3rd sub-layer)
    outputs = tf.keras.layers.Dense(units=dff, activation='relu')(attention2)
    outputs = tf.keras.layers.Dense(units=d_model)(outputs)

    # dropout & residual connnection & layer normalization
    outputs = tf.keras.layers.Dropout(rate=dropout)(outputs)
    outputs = tf.keras.layers.LayerNormalization(epsilon=1e-6)(outputs + attention2)

    return tf.keras.Model(inputs=[inputs, enc_outputs, look_ahead_mask, padding_mask], outputs=outputs, name=name)

def decoder(vocab_size, num_layers, dff, d_model, num_heads, dropout, name='decoder'):
    inputs = tf.keras.Input(shape=(None,), name='inputs')
    enc_outputs = tf.keras.Input(shape=(None, d_model), name='encoder_outputs')

    # masks
    look_ahead_mask = tf.keras.Input(shape=(1,None,None), name='look_ahead_mask')
    padding_mask = tf.keras.Input(shape=(1,1,None), name='padding_mask')

    # embedding & positional encoding & dropout
    embeddings = tf.keras.layers.Embedding(vocab_size, d_model)(inputs)
    embeddings *= tf.math.sqrt(tf.cast(d_model, tf.float32))
    embeddings = PositionalEncoding(vocab_size, d_model)(embeddings)
    outputs = tf.keras.layers.Dropout(rate=dropout)(embeddings)

    # stack decoder by the number of num_layers
    for i in range(num_layers):
        outputs = decoder_layer(dff=dff, d_model=d_model, num_heads=num_heads, dropout=dropout, name='decoder_layer_{}'.format(i))(inputs=[outputs, enc_outputs, look_ahead_mask, padding_mask])

    return tf.keras.Model(inputs=[inputs, enc_outputs, look_ahead_mask, padding_mask], outputs=outputs, name=name)

# entire transformer model
def transformer(vocab_size, num_layers, dff, d_model, num_heads, dropout, name="transformer"):
    # input of encoder
    inputs = tf.keras.Input(shape=(None,), name="inputs")

    # input of decoder
    dec_inputs = tf.keras.Input(shape=(None,), name="dec_inputs")

    # padding mask of encoder
    enc_padding_mask = tf.keras.layers.Lambda(create_padding_mask, output_shape=(1,1,None), name='enc_padding_mask')(inputs)

    # look-ahead mask of decoder
    look_ahead_mask = tf.keras.layers.Lambda(create_look_ahead_mask, output_shape=(1, None, None), name='look_ahead_mask')(dec_inputs)

    # padding mask of decoder
    dec_padding_mask = tf.keras.layers.Lambda(create_padding_mask, output_shape=(1,1,None), name='dec_padding_mask')(inputs)

    # output of encoder
    enc_outputs = encoder(vocab_size=vocab_size, num_layers=num_layers, dff=dff, d_model=d_model, num_heads=num_heads, dropout=dropout)(inputs=[inputs, enc_padding_mask])

    dec_outputs = decoder(vocab_size=vocab_size, num_layers=num_layers, dff=dff, d_model=d_model, num_heads=num_heads, dropout=dropout)(inputs=[dec_inputs, enc_outputs, look_ahead_mask, dec_padding_mask])

    # output layer
    outputs = tf.keras.layers.Dense(units=vocab_size, name="outputs")(dec_outputs)

    return tf.keras.Model(inputs=[inputs, dec_inputs], outputs=outputs, name=name)

def loss_function(y_true, y_pred):
    y_true = tf.reshape(y_true, shape=(-1, MAX_LENGTH - 1))

    loss = tf.keras.losses.SparseCategoricalCrossentropy(
      from_logits=True, reduction='none')(y_true, y_pred)

    mask = tf.cast(tf.not_equal(y_true, 0), tf.float32)
    loss = tf.multiply(loss, mask)

    return tf.reduce_mean(loss)

class CustomSchedule(tf.keras.optimizers.schedules.LearningRateSchedule):
    def __init__(self, d_model, warmup_steps=4000):
        super(CustomSchedule, self).__init__()
        self.d_model = d_model
        self.d_model = tf.cast(self.d_model, tf.float32)
        self.warmup_steps = warmup_steps

    def __call__(self, step):
        arg1 = tf.math.rsqrt(step)
        arg2 = step * (self.warmup_steps**-1.5)

        return tf.math.rsqrt(self.d_model) * tf.math.minimum(arg1, arg2)



# load chatbot data
urllib.request.urlretrieve("https://raw.githubusercontent.com/songys/Chatbot_data/master/ChatbotData.csv", filename="ChatBotData.csv")
train_data=pd.read_csv('ChatBotData.csv')
print("------- train data -------")
print("### first 5 sample ###")

train_data.head()

print('the number of chatbot samples : ', len(train_data))

print("### check if there is unnecessary Null ###")
print(train_data.isnull().sum())

print("------------------------------------------")

questions = []
for sentence in train_data['Q']:
    # 구두점에 대해서 띄어쓰기
    # ex) 12시 땡! -> 12시 땡 !
    sentence = re.sub(r"([?.!,])", r" \1 ", sentence)
    sentence = sentence.strip()
    questions.append(sentence)

answers = []
for sentence in train_data['A']:
    # 구두점에 대해서 띄어쓰기
    # ex) 12시 땡! -> 12시 땡 !
    sentence = re.sub(r"([?.!,])", r" \1 ", sentence)
    sentence = sentence.strip()
    answers.append(sentence)


print("------- check train data for spliting '.' -------")
print("### first 5 sample ###")

print(questions[:5])
print(answers[:5])

print("--------------------------------------------------")

# using sub-word text encoder, generate vocabulary set from Question & Answer data
tokenizer = tfds.deprecated.text.SubwordTextEncoder.build_from_corpus(questions + answers, target_vocab_size = 2**13)

# integer for start token (SOS) and end token (EOS)
START_TOKEN, END_TOKEN = [tokenizer.vocab_size], [tokenizer.vocab_size + 1]

# to include start token and end token, increase the size of vocab
VOCAB_SIZE = tokenizer.vocab_size + 2

print('No. start token :',START_TOKEN)
print('No. end token :',END_TOKEN)
print('size of vocab set :',VOCAB_SIZE)

# integer encoding (text sequence --> integer sequence)
MAX_LENGTH = 40

def tokenize_and_filter(inputs, outputs):
    # tokenize & integer encoding & add start token, end token & padding
    tokenized_inputs, tokenized_outputs = [], []

    for (sentence1, sentence2) in zip(inputs, outputs):
        sentence1 = START_TOKEN + tokenizer.encode(sentence1) + END_TOKEN
        sentence2 = START_TOKEN + tokenizer.encode(sentence2) + END_TOKEN

        tokenized_inputs.append(sentence1)
        tokenized_outputs.append(sentence2)

    # padding
    tokenized_inputs = tf.keras.preprocessing.sequence.pad_sequences(tokenized_inputs, maxlen=MAX_LENGTH, padding='post')
    tokenized_outputs = tf.keras.preprocessing.sequence.pad_sequences(tokenized_outputs, maxlen=MAX_LENGTH, padding='post')

    return tokenized_inputs, tokenized_outputs

questions, answers = tokenize_and_filter(questions, answers)

print('shape of question data :', questions.shape)
print('shape of answer data :', answers.shape)

# 텐서플로우 dataset을 이용하여 셔플(shuffle)을 수행하되, 배치 크기로 데이터를 묶는다.
# 또한 이 과정에서 교사 강요(teacher forcing)을 사용하기 위해서 디코더의 입력과 실제값 시퀀스를 구성한다.
BATCH_SIZE = 64
BUFFER_SIZE = 20000

# 디코더의 실제값 시퀀스에서는 시작 토큰을 제거해야 한다.
dataset = tf.data.Dataset.from_tensor_slices((
    {
        'inputs': questions,
        'dec_inputs': answers[:, :-1] # 디코더의 입력. 마지막 패딩 토큰이 제거된다.
    },
    {
        'outputs': answers[:, 1:]  # 맨 처음 토큰이 제거된다. 다시 말해 시작 토큰이 제거된다.
    },
))

dataset = dataset.cache()
dataset = dataset.shuffle(BUFFER_SIZE)
dataset = dataset.batch(BATCH_SIZE)
dataset = dataset.prefetch(tf.data.experimental.AUTOTUNE)

tf.keras.backend.clear_session()

# hyperparameter
D_MODEL = 256
NUM_LAYERS = 2
NUM_HEADS = 8
DFF = 512
DROPOUT = 0.1

model = transformer(vocab_size = VOCAB_SIZE, num_layers = NUM_LAYERS, dff=DFF, d_model = D_MODEL, num_heads = NUM_HEADS, dropout=DROPOUT)

# define learning rate and optimizer
learning_rate = CustomSchedule(D_MODEL)

optimizer = tf.keras.optimizers.legacy.Adam(learning_rate, beta_1=0.9, beta_2=0.98, epsilon=1e-9)

def accuracy(y_true, y_pred):
    # label size : batch_size * MAX_LENGTH - 1
    y_true = tf.reshape(y_true, shape=(-1, MAX_LENGTH-1))
    return tf.keras.metrics.sparse_categorical_accuracy(y_true, y_pred)

# compile model
model.compile(optimizer=optimizer, loss=loss_function, metrics=[accuracy])

# the number of training is set as EPOCHS
EPOCHS = 50
model.fit(dataset, epochs = EPOCHS)


# -------- evaluation of chatbot --------
def preprocess_sentence(sentence):
    # 단어와 구두점 사이에 공백 추가.
    # ex) 12시 땡! -> 12시 땡 !
    sentence = re.sub(r"([?.!,])", r" \1 ", sentence)
    sentence = sentence.strip()
    return sentence

def evaluate(sentence):
    # 입력 문장에 대한 전처리
    sentence = preprocess_sentence(sentence)

    # 입력 문장에 시작 토큰과 종료 토큰을 추가
    sentence = tf.expand_dims(
        START_TOKEN + tokenizer.encode(sentence) + END_TOKEN, axis=0)

    output = tf.expand_dims(START_TOKEN, 0)

    # 디코더의 예측 시작
    for i in range(MAX_LENGTH):
        predictions = model(inputs=[sentence, output], training=False)

        # 현재 시점의 예측 단어를 받아온다.
        predictions = predictions[:, -1:, :]
        predicted_id = tf.cast(tf.argmax(predictions, axis=-1), tf.int32)

        # 만약 현재 시점의 예측 단어가 종료 토큰이라면 예측을 중단
        if tf.equal(predicted_id, END_TOKEN[0]):
            break

    # 현재 시점의 예측 단어를 output(출력)에 연결한다.
    # output은 for문의 다음 루프에서 디코더의 입력이 된다.
    output = tf.concat([output, predicted_id], axis=-1)

    # 단어 예측이 모두 끝났다면 output을 리턴.
    return tf.squeeze(output, axis=0)

def predict(sentence):
    prediction = evaluate(sentence)

    # prediction == 디코더가 리턴한 챗봇의 대답에 해당하는 정수 시퀀스
    # tokenizer.decode()를 통해 정수 시퀀스를 문자열로 디코딩.
    predicted_sentence = tokenizer.decode([i for i in prediction if i < tokenizer.vocab_size])

    print('Input: {}'.format(sentence))
    print('Output: {}'.format(predicted_sentence))

    return predicted_sentence
 
# chatbot execution

output = predict("안녕?")
output = predict("나 할말이 있어.")
output = predict("나랑 게임하자!")
output = predict("너는 나에 대해 어떻게 생각해?")
output = predict("너 똑똑해?")
output = predict("너는 한낱 컴퓨터일 뿐이야.")
output = predict("넌 무슨 음식 좋아해?")
output = predict("너가 싫어.")
output = predict("난 너가 좋아.")
