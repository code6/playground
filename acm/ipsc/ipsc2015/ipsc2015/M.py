from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())
import random

def main():
    d = "![]+-*"
    m = {}
    m[0] = "+![]"
    m[1] = "+!![]"
    m[2] = "!![]+!![]"
    for i in xrange(3, 1001):
        m[i] =  "%s+%s" % (m[1], m[i - 1])
        for j in xrange(2, i / 2 + 1):
            t = "%s+%s" % (m[j], m[i - j])
            if len(m[i]) > len(t):
                m[i] = t
            if i % j == 0:
                t = "[%s]*[%s]" % (m[j], m[i / j])
                if len(m[i]) > len(t):
                    m[i] = t
    for i in xrange(1001):
        print m[i]


if __name__ == '__main__':
    main()
