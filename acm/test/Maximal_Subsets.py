from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def rec(cur, cur_sum, avail, idx,  n, s, k):
    if idx == n:
        next_avail = avail
    else:
        next_avail = s[idx] if avail == 0 else min(avail, s[idx])
    if cur_sum + next_avail > k:
        print cur
        return
    for pos in xrange(idx, n):
        if cur_sum + s[pos] > k:
            continue
        cur.append(s[pos])
        rec(cur, cur_sum + s[pos], avail if pos ==idx else next_avail, pos + 1, n, s, k)
        cur.pop()

def main():
    n, k = read_ints()
    s = read_ints()
    s.sort()
    rec([], 0, 0, 0, n, s,  k)

if __name__ == '__main__':
    main()
