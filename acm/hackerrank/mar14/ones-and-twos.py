#coding=utf8
import sys
sys.setrecursionlimit(10000) # 10000 is an example, try with different values
from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

MOD = 10 ** 9 + 7

def get_max(level, left):
    ret = 0
    while left and level:
        ret += 2 ** level
        left -= level
        level = min(level - 1, left)
    return ret

memo = {}

def rec(level, left, threshold):
    global memo
    #assume left >= level
    level = min(level, left)
    if level <= 0:
        return 0
    if (level, left) in memo:
        return memo[(level, left)]
    #print level, left, threshold
    ret = 0
    diff = 2 ** level - get_max(level - 1, left) - 1
    if diff > threshold:
        ret += (diff - threshold) % MOD
    ret += rec(level - 1, left - level, threshold) + rec(level - 1, left, threshold)
    memo[(level, left)] = ret
    return ret


def main():
    global memo
    t = read_ints()[0]
    for cas in xrange(t):
        memo = {}
        a, b = read_ints()
        ret = get_max(b, b) + a - rec(b, b, a)
        ret = (ret % MOD + MOD) % MOD
        print ret

if __name__ == '__main__':
    main()
