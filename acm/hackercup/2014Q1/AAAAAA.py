from collections import Counter, defaultdict
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def main():
    t = read_ints()[0]
    for i in xrange(t):
        cas = i + 1
        n, m = read_ints()
        dp = [] 
        max_val = []

        board = []
        for i in xrange(n):
            board.append(raw_input())
            max_val.append([-1] * m)
            dp.append([-1] * m)

        dp[0][0] = 1
        for i in xrange(n):
            for j in xrange(m):
                pv = dp[i][j]
                if pv > 0:
                    if i + 1 < n and board[i+1][j] != '#':
                        dp[i+1][j] = max(dp[i+1][j], pv + 1)
                    if j + 1 < m and board[i][j + 1] != '#':
                        dp[i][j + 1] = max(dp[i][j + 1], pv + 1)
                ni = n - 1 - i
                nj = m - 1 - j
                if board[ni][nj] != '#':
                    max_val[ni][nj] = 1
                    if ni + 1 < n:
                        max_val[ni][nj] = max(max_val[ni][nj], max_val[ni + 1][nj] + 1)
                    if nj + 1 < m:
                        max_val[ni][nj] = max(max_val[ni][nj], max_val[ni][nj + 1] + 1)
        #not use
        ans = max_val[0][0]

        #use one upper contiguous section
        for j in xrange(m):
            down_val = -1 
            for _i in xrange(n):
                i = n - 1 - _i
                if board[i][j] != '#':
                    left_val = -1
                    if j and (dp[i][j-1] >= 0):
                        left_val = dp[i][j-1]
                    if down_val == -1 and left_val == -1:
                        continue
                    tmp = max(left_val, down_val) + 1
                    down_val = tmp
                    if j + 1 < m:
                        tmp = max(tmp, tmp + max_val[i][j+1])
                    ans = max(ans, tmp)
                else:
                    down_val = -1

        #use one leftwards contiguous section
        for i in xrange(n):
            right_val = -1 
            for _j in xrange(m):
                j = m - 1 - _j
                if board[i][j] != '#':
                    upper_val = -1
                    if i and (dp[i - 1][j] >= 0):
                        upper_val = dp[i -1][j]
                    if upper_val == -1 and right_val == -1:
                        continue
                    tmp = max(upper_val, right_val) + 1
                    right_val = tmp
                    if i + 1 < n:
                        tmp = max(tmp, tmp + max_val[i+1][j])
                    ans = max(ans, tmp)
                else:
                    right_val = -1
        print "Case #%d: %s" % (cas,  ans)

if __name__ == '__main__':
    main()
