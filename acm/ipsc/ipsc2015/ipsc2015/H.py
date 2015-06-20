from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def bitsoncount(x):
    return bin(x).count('1')

def two(i):
    return 1 << i

mem = {}
def rec(n, d, x, y, vx, vy, t):
    if (x, y) in mem:
        return mem[(x, y)]
    if t == n:
        return (vx + vy, abs(vx - vy))
    lx, ly = rec(n, d, x + two(t), y, vx + bitsoncount(d[t] & x), vy, t + 1)
    rx, ry = rec(n, d, x, y + two(t), vx, vy + bitsoncount(d[t] & y), t + 1)
    mem[(x,y)] = (max(lx, rx), min(ly, ry))
    return mem[(x,y)]

def main():
    t = read_ints()[0]
    for cas in xrange(t):
        raw_input()
        n, m = read_ints()
        d = {}
        for i in xrange(n):
            d[i] = 0
        for i in xrange(m):
            x, y = read_ints()
            x -= 1
            y -= 1
            if x > y:
                x,y = y,x
            d[y] += two(x)

        global mem 
        mem = {}
        q1, q2 = rec(n, d, 1, 2, 0, 0, 2)
        print q1, q2

if __name__ == '__main__':
    main()
