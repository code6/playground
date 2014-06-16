from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout

def read_ints(skip=True):
    inp = raw_input()
    while skip:
        if not inp:
            inp = raw_input()
        else:
            break
    return  map(int, inp.split())

read_floats = lambda: map(float, raw_input().split())


mem = {}
def rec(dep, used, avail):
    if (dep, used) in mem:
        return mem[(dep, used)]
    ret = False
    for p, l in enumerate(avail):
        if dep <= l and (used & (2**p) == 0):
            tmp = rec(dep + 1, used | 2 ** p, avail)
            if not tmp:
                ret = True
                break
    mem[(dep, used)] = ret
    return ret


def main():
    t = read_ints()[0]
    for cas in xrange(t):
        n = read_ints()[0]
        arr = raw_input().strip()
        avail = []
        for i in xrange(n):
            if arr[i] == '1':
                avail.append(i)
        global mem
        mem = {}
        ans = rec(0, 0, avail)

        if ans:
            print "Adam"
        else:
            print "Betka"

if __name__ == '__main__':
    main()
