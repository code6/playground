from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def main():
    t = read_ints()[0]
    for cas in xrange(t):
        C, F, X = read_floats()
        ans =  X / 2.0
        s = 0.0
        # lim = int(max(0, X - 2) / F + 10)
        lim = int(X + 10)
        bd = 0
        for i in xrange(lim):
            cn = i + 1
            s += C / (2.0 + (cn - 1) * F)
            if s > ans:
                break
            ans = min(ans, s + X / (2.0 + cn * F))
        print "Case #%d: %.7f" % (cas + 1, ans)

if __name__ == '__main__':
    main()
