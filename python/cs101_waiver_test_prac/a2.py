import random

FACES = list(range(2,11)) + ['Jack', 'Queen', 'King', 'Ace']
SUITS = ['Clubs', 'Diamonds', 'Hearts', 'Spades']

class Card(object):
    def __init__(self, face, suit):
        self.face = face
        self.suit = suit

    def __str__(self):
        article = "a "
        if self.face in [8, "Ace"]:
            article = "an "

        return article + str(self.face) + " of " + self.suit

    def value(self):
        if type(self.face) == int:
            return self.face
        elif self.face == "Ace":
            return 11
        else:
            return 10

class Deck(object):
    def __init__(self):
        self.cards = []
        for suit in SUITS:
            for face in FACES:
                self.cards.append(Card(face, suit))
        
        random.shuffle(self.cards)

    def draw(self):
        return self.cards.pop()

def hand_value(hand):
    value_cnt = 0
    for card in hand:
        value_cnt += card.value()

    return value_cnt

def ask_yesno():
    while(True):
        user_input = input("Another Deck? (y/n): ")

        if user_input == 'y':
            return True
        elif user_input == 'n':
            return False
        else: 
            print("input again")

def blackjack():
    deck = Deck()

    dealer = []
    player = []

    player.append(deck.draw())
    print("you dealt", player[0])
    dealer.append(deck.draw())
    print("dealer dealt hidden card")
    player.append(deck.draw())
    print("you dealt", player[1])
    dealer.append(deck.draw())
    print("dealer dealt", dealer[1])
    print("your total is", hand_value(player))

    while (hand_value(player) < 21) :
        if not ask_yesno():
            break;
        
        player.append(deck.draw())

        print("you dealt", player[-1])
        print("your total is", hand_value(player))

    if (hand_value(player) > 21):
        print("over 21, lose")
        return -1

    print("dealer's hidden card was", dealer[0])

    while (hand_value(dealer) < 17):
        dealer.append(deck.draw())
        print("Dealer dealt", dealer[-1])

    print("dealer total is", hand_value(dealer))

    if (hand_value(dealer) > 21):
        print("dealer over 21, you win")
        return 1

    
    print("your total is", hand_value(player))

    print("dealer total is", hand_value(dealer))

    if hand_value(player) > hand_value(dealer):
        print("You win")
        return 1
    elif hand_value(player) < hand_value(dealer):
        print("You lose")
        return -1
    else:
        print("tie")
        return 0

print("welcome")
while True:
    print
    blackjack()
    flag = 0
    while(True):
        ask_input = input("\n want to play another round (y/n) ")
        if ask_input == 'y':
            break;
        elif ask_input == 'n':
            flag = 1
            break;
        else:
            print("wrong input")
    
    if flag == 1:
        break


