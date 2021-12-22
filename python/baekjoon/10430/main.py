arr = list(map(int, input().split()))
ans = list()

ans.append((arr[0] + arr[1])%arr[2])
ans.append(((arr[0] % arr[2]) + (arr[1] % arr[2]))%arr[2])
ans.append((arr[0] * arr[1])%arr[2])
ans.append(((arr[0] % arr[2]) * (arr[1] % arr[2]))%arr[2])

for i in range(4):
    print(ans[i])

