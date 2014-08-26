from collections import Counter, defaultdict
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def calc(state, _s):
    s = _s.copy()
    INF = 10000
    ans = 0
    for i in xrange(10):
        if state & 2 ** i:
            ans += 1
    for i in xrange(5):
        if state & (2 ** i):
            for _j in xrange(5):
                j = _j + 4
                if state & (2 ** j):
                    if (i, j) in s:
                        s.remove((i, j))

    cnt = Counter()
    for v in s:
        cnt[v[0]] += 1
        cnt[v[1]] += 1

    while s:
        found = False
        for k, v in cnt.iteritems():
            if v == 1:
                for p in s:
                    if (p[0] == k or p[1] == k):
                        cnt[p[0]] -= 1
                        cnt[p[1]] -= 1
                        s.remove(p)
                        found = True
                        break
                break
        if found:
            continue
        return INF
    return ans

def main():
    n = read_ints()[0]
    cards = [c.strip() for c in raw_input().strip().split(' ') if c.strip()]
    COLOR = "RGBYW"
    s = set()
    for c in cards:
        s.add((COLOR.index(c[0]), int(c[1])  + 4))

    ans = 1000
    for state in xrange(2 ** 10):
        steps = calc(state, s)
        if steps < ans:
            print state, steps
            ans = steps
    print ans

if __name__ == '__main__':
    main()
