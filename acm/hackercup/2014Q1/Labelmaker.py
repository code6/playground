from collections import Counter, defaultdict
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def main():
    t = read_ints()[0]
    for i in xrange(t):
        cas = i + 1
        words, n = raw_input().split()
        wl = len(words)
        n = int(n)
        l = 1
        while True:
            if (wl ** l) >= n:
                break
            n -= wl ** l
            l += 1
        ans = ''
        for i in xrange(l):
            add = wl ** (l - i - 1)
            for c in xrange(wl):
                if n > add:
                    n -= add
                else:
                    ans += words[c]
                    break

        print "Case #%d: %s" % (cas,  ans)

if __name__ == '__main__':
    main()
