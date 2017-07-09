from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def solve(n):
    print n - 1
    base = -10000
    for i in xrange(n - 1):
        print 0, base + i


def work():
    ret = []
    t = read_ints()[0]
    read_ints()
    for i in xrange(t):
        n = read_ints()[0]
        read_ints()
        solve(n)
    return ret

def main():
    work()
    

if __name__ == '__main__':
    main()
