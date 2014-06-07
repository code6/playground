#coding=utf8
from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def two(n, m):
    ret = set()
    ret.add(0)
    if (m < 1 or n == 0):
        return ret
    ma = min(n, m)
    for i in xrange(ma):
        pw = i + 1
        last = 2 ** pw
        s = two(n - pw, pw - 1)
        for v in s:
            ret.add(last + v)
    return ret

def main():
    for i in xrange(15):
        ret = sorted([ v for v in two(i, i)])
        print i, 
        base = 1
        for v in ret:
            if base < v:
                base *= 2
                print ',', 
            print v,
        print 
    

if __name__ == '__main__':
    main()
