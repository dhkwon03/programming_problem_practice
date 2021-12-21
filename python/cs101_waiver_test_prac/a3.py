def merge(l_arr, r_arr):
    result = []

    l_idx = 0
    r_idx = 0

    while l_idx < len(l_arr) and r_idx < len(r_arr):
        if l_arr[l_idx] <= r_arr[r_idx]:
            result.append(l_arr[l_idx])
            l_idx += 1
        else:
            result.append(r_arr[r_idx])
            r_idx += 1

    result += l_arr[l_idx:]
    result += r_arr[r_idx:]

    return result



def merge_sort(a):
    if len(a) <= 1:
        return a

    middle = len(a) // 2

    left_arr = a[:middle]
    right_arr = a[middle:]

    l_res = merge_sort(left_arr)
    r_res = merge_sort(right_arr)

    return merge(l_res, r_res) 

arr = [4,7,6,3,2,5,7,8,4,3,6,9]

print(merge_sort(arr))



        

