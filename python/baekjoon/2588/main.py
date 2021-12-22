num1 = int(input())
num2 = int(input())

num2_separate = list()
num2_separate.append((num2 % 10) * num1)
num2_separate.append((num2 // 10 % 10) * num1)
num2_separate.append((num2 // 100) * num1)

ans = num2_separate[0] + num2_separate[1] * 10 + num2_separate[2] * 100;

for i in range(3):
    print(num2_separate[i])

print(ans)
