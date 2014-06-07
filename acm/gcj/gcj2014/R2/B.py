
from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
import sys
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())
sys.setrecursionlimit(99999) 

INF = 100000000

def solve(n, cache, pos, le, ri):
    if (le, ri) in cache:
        return cache[(le, ri)]
    if le + ri == n:
        return 0
    ret = INF
    ne = le + ri
    #move left
    lc = len([rank for rank, p in enumerate(pos) if rank > ne and  p < pos[ne]])
    ret = min(ret, solve(n, cache, pos, le+1, ri) + lc)
    #move right
    rc = len([rank for rank, p in enumerate(pos) if rank > ne and  p > pos[ne]])
    ret = min(ret, solve(n, cache, pos, le, ri+1) + rc)
    cache[(le, ri)] = ret
    return ret

def main():
    T = read_ints()[0]
    for i in xrange(T):
        cas = i + 1
        n = read_ints()[0]
        arr = read_ints()
        brr = []
        for i in xrange(n):
            brr.append([arr[i], i])
        brr  = sorted(brr, key=lambda brr:brr[0])
        pos = []
        for i in xrange(n):
            pos.append(brr[i][1])

        cache = {}
        ans = solve(n, cache, pos, 0, 0)
        print "Case #%d: %d" % (cas, ans)

if __name__ == '__main__':
    main()
