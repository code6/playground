from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
import string
import math
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

#union-find
def ufind(par, pos):
    if pos == par[pos]:
        return pos
    par[pos] = ufind(par, par[pos])
    return par[pos]

def uunion(par, x, y):
    x = ufind(par, x)
    y = ufind(par, y)
    if x == y:
        return 
    par[x] = y

def is_one(w):
    for ch in w:
        if ch != w[0]:
            return False
    return True

def run(arr):
    n = len(arr)

    #check illegal
    left_cnt = Counter()
    left_pid = {}
    right_pid = {}
    right_cnt = Counter()
    inter_cnt = Counter()
    one_cnt = Counter()

    par = []
    for i in xrange(len(arr)):
        par.append(i)

    for wpos, w in enumerate(arr):
        wl = []
        pre = w[0]
        for ch in w:
            if ch != pre:
                wl.append(pre)
                pre = ch
        wl.append(pre)
        if len(wl) == 1:
            one_cnt[wl[0]] += 1
        else:
            for pos, w in enumerate(wl):
                if pos == 0:
                    left_cnt[w] += 1
                    left_pid[w] = wpos
                elif pos == len(wl) - 1:
                    right_cnt[w] += 1
                    right_pid[w] = wpos
                else:
                    inter_cnt[w] += 1

    kinds = 0
    for ch in string.lowercase:
        #print ch, one_cnt[ch], left_cnt[ch], right_cnt[ch], inter_cnt[ch]
        if inter_cnt[ch]:
            if one_cnt[ch] or left_cnt[ch] or right_cnt[ch] or inter_cnt[ch] > 1:
                return 0
        else:
            if left_cnt[ch] or right_cnt[ch]:
                if left_cnt[ch] > 1 or right_cnt[ch] > 1:
                    return 0
                if left_cnt[ch] and right_cnt[ch]:
                    #need connect
                    x = left_pid[ch]
                    y = right_pid[ch]
                    if ufind(par, x) == ufind(par, y):
                        return 0
                    uunion(par, x, y)
            else:
                if one_cnt[ch]:
                    kinds += 1

    ks = set()
    for i in xrange(n):
        if not is_one(arr[i]):
            ks.add(ufind(par, i))
    kinds += len(ks)

    ans = math.factorial(kinds)
    for v in one_cnt.values():
        ans *= math.factorial(v)
    ans = ans % 1000000007
    return ans


def main():
    T = read_ints()[0]
    for i in xrange(T):
        cas = i + 1
        n = read_ints()[0]
        arr = raw_input().split()
        print "Case #%d: %d" %( cas, run(arr))

if __name__ == '__main__':
    main()
