def hot_cold(emotion):
    #카운팅을 해야되니까 몇 개 인지 저장할 변수
    cnt = 0

    #flag 라는 거를 처음에는 0으로 설정했다가 냉정이나 열정이 나오면 1로 바꾸는 거야!
    #그래서 flag == 1 일 때만 cnt = cnt + 1 해주고
    #flag == 1이면서 "냉정" 이나 "열정" 이 나오면
    #flag = 0 으로 다시 설정해주는 거야
    #그럼 그 다음에는 다시 안 세겠지?
    flag = 0

    for i in emotion:
        if flag == 1 :
            #cnt 추가해줘

            if i == "냉정" or i == "열정" :
                #여기는 직접 넣어봐(flag 에 무슨 값을 넣을지 생각해봐)
        else :
            if i == "냉정" or i == "열정" :
                #여기는 직접 넣어봐(flag 에 무슨 값을 넣을지 생각해봐)
                cnt -= 1 # 이거는 ... cnt 가 순서상 하나 더 더해지기 때문에 하나 빼야돼

    return cnt

    print(hot_cold([#안적을께..]))
