from collections import Counter, defaultdict
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def main():
    t = read_ints()[0]
    for i in xrange(t):
        cas = i + 1
        n, k, c = read_ints()
        ans = 10 ** 15

        for unused in xrange(n):
            used = n - unused
            x = k / used
            le = k % used
            tmp = unused
            if x * used >= c:
                tmp += c
            else:
                tmp += c + ((used - le) % used)
            ans = min(ans, tmp)
        
        print "Case #%d: %s" % (cas,  ans)

if __name__ == '__main__':
    main()
