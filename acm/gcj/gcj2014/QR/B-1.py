from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def main():
    t = read_ints()[0]
    for cas in xrange(t):
        C, F, X = read_floats()
        res =  X / 2.0
        et = 0.0
        nf = 0.0
        bd = 0
        while True:
            cd = 2 + nf * F
            if et + X / cd < res:
                bd = nf
            res = min(res, et + X / cd)
            wt = C / cd
            et += wt
            nf += 1.0
            if et > res:
                break
        print "Case #%d: %.7f" % (cas + 1, res)

if __name__ == '__main__':
    main()
