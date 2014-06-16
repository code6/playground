from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
import sys
sys.setrecursionlimit(99999)
import heapq

def read_ints(skip=True):
    inp = raw_input()
    while skip:
        if not inp:
            inp = raw_input()
        else:
            break
    return  map(int, inp.split())

def calc(w):
    ret = 0
    heapq.heapify(w)
    while len(w) > 1:
        x = heapq.heappop(w)
        y = heapq.heappop(w)
        heapq.heappush(w, x + y)
        ret += x + y
    return ret

def solve(g, cur, pre):
    ret, weight = 0,0
    w = []
    for ne in g[cur]:
        if ne == pre:
            continue
        (sr, sw) = solve(g, ne, cur)
        ret += sr
        w.append(sw)
    ret += calc(w)
    weight = sum(w) + 1
    #print cur + 1, ret, weight
    return ret, weight

def main():
    t = read_ints()[0]
    for cas in xrange(t):
        n = read_ints()[0]
        arr = read_ints()
        g = {}
        w = {}
        for i in xrange(n - 1):
            v = arr[i] - 1
            g.setdefault(v, []).append(i + 1)
            g.setdefault(i + 1, []).append(v)
        
        ans = solve(g, 0, -1)[0]
        print ans

if __name__ == '__main__':
    main()
