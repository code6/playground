from collections import Counter, defaultdict
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def main():
    n = read_ints()[0]
    arr =read_ints()
    arr.sort()
    sum = 0
    for i in xrange(n):
        sum += (i + 2) * arr[i]
    sum-= arr[n - 1]
    print sum

if __name__ == '__main__':
    main()
