import base64

encode_str1 = 'admin'
encode_str2 = 'nimda'

encode_str_bytes1 = encode_str1.encode("ascii")
encode_str_bytes2 = encode_str2.encode("ascii")



for i in range(0,20):
    encode_str_bytes1 = base64.b64encode(encode_str_bytes1)
    encode_str_bytes2 = base64.b64encode(encode_str_bytes2)

encode_str1_ans = encode_str_bytes1.decode("ascii")
encode_str2_ans = encode_str_bytes2.decode("ascii")

print(encode_str1_ans)
print(encode_str2_ans)
