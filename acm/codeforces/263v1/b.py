from collections import Counter, defaultdict
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

MOD = 10 ** 9 + 7

def addEdge(g, x, y):
    if not x in g:
        g[x] = []
    if not y in g:
        g[y] = []
    g[x].append(y)
    g[y].append(x)

def rec(g, n, col, cur, par):
    b, w = int(col[cur] == 1), int(col[cur] == 0)
    for ne in g[cur]:
        if ne == par:
            continue
        sb, sw = rec(g, n, col, ne, cur)
        _b = (w * sb + b * (sw + sb)) % MOD
        _w = (w * (sw + sb)) % MOD
        #print cur, ne, b, w, _b, _w
        b, w = _b, _w
    #print "rec ", cur, b, w
    return b, w



def main():
    n = read_ints()[0]
    p = read_ints()
    c = read_ints()
    g = {}
    for i in xrange(n-1):
        x = i + 1
        y = p[i]
        addEdge(g, x, y)
    res = {}
    b, _ = rec(g, n, c,  0, -1)
    print  b

if __name__ == '__main__':
    main()
