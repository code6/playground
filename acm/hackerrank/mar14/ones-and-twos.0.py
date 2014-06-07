#coding=utf8
from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def get_max(level, left):
    ret = 0
    while left and level:
        ret += 2 ** level
        left -= level
        level = min(level - 1, left)
    return ret

def rec(level, left, threshold):
    #assume left >= level
    level = min(level, left)
    if level <= 0:
        return 0
    #print level, left, threshold
    ret = 0
    diff = 2 ** level - get_max(level - 1, left) - 1
    if diff > threshold:
        ret += diff - threshold
    ret += rec(level - 1, left - level, threshold) + rec(level - 1, left, threshold)
    return ret


def main():
    t = read_ints()[0]
    for cas in xrange(t):
        a, b = read_ints()
        print get_max(b, b) + a - rec(b, b, a)

if __name__ == '__main__':
    main()
