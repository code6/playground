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

def main():
    t = read_ints()[0]
    for cas in xrange(t):
        n = read_ints()[0]
        arr = read_ints()
        ans = []
        d = set()
        for val in arr:
            if val in d:
                continue
            ans.append(str(val))
            d.add(val)
        print " ".join(ans)

if __name__ == '__main__':
    main()
