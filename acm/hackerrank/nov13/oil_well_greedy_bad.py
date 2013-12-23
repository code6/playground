from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
from copy import copy
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def dis(arr, i, j):
    return max(max(abs(i - ai), abs(j - aj)) for (ai, aj) in arr)

def test(arr, i, j):
    ret = 0
    choose = [(i, j)]
    arr[i][j] = 0
    while True:
        best_dis = -1
        bx, by = -1, -1
        for x in xrange(len(arr)):
            for y in xrange(len(arr[0])):
                if arr[x][y]:
                    tmp_dis = dis(choose, x, y)
                    if tmp_dis < best_dis or best_dis == -1:
                        best_dis = tmp_dis
                        bx, by = x, y
        if best_dis == -1:
            return ret
        ret += best_dis
        arr[bx][by] = 0
        choose.append((bx, by))

def main():
    n, m = read_ints()
    arr = []
    for i in xrange(n):
        arr.append(read_ints())
    ans = None
    for i in xrange(n):
        for j in xrange(m):
          if arr[i][j]:
            tmp = test(copy(arr), i, j)
            if ans:
                ans = min(ans, tmp)
            else:
                ans = tmp
                
    print ans

if __name__ == '__main__':
    main()
