from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
import sys

def main():
    f = sys.argv[1]
    s = open(f).read()
    for c in s:
        if c != "\0":
            print c,

if __name__ == '__main__':
    main()
