def three_doubles(word):
    s = ""

    conti = 0
    count = 0        
    for i in range(len(word)):
        if word[i - 1] == word[i]:
            count += 1
            conti = 1
        else:
            if conti == 1:
                conti = 0
                continue
            else:
                count = 0

        if count == 3:
            return True
                


    
    return False 



print(three_doubles("Commttee"))

