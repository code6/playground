from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def fill(bo, left):
    if not left:
        return True
    R = len(bo)
    C = len(bo[0])
    if R == 1:
        for i in xrange(left):
            bo[0][i + 1] = '.'
        return True
    elif C == 1:
        for i in xrange(left):
            bo[i + 1][0] = '.'
        return True
    else:
        if left < 3:
            return False
        bo[0][1] = bo[1][0] = bo[1][1] = '.'
        left -= 3
        mr = mc = 1
        while left >= 2 and (mr + 1 < R or mc + 1 < C):
            if mr + 1 < R and left >= 2:
                mr += 1
                bo[mr][0] = bo[mr][1] = '.'
                left -= 2
            if mc + 1 < C and left >= 2:
                mc += 1
                bo[0][mc] = bo[1][mc] = '.'
                left -= 2
        if not left:
            return True
        if mr < 2 or mc < 2 or (mr - 1) * (mc - 1) < left:
            return False

        for i in xrange(left):
            x, y = i / (mc - 1) + 2 , i % (mc - 1) + 2
            bo[x][y] = '.'

        return True


def main():
    t = read_ints()[0]
    for cas in xrange(t):
        R, C, M = read_ints()
        bo = [["*"] * C for i in xrange(R) ] 
        left = R * C - 1 - M
        bo[0][0] = 'c'
        legal = fill(bo, left)
        print "Case #%d:" % (cas + 1)
        if legal:
            for i in xrange(len(bo)):
                print "".join(bo[i])
        else:
            print "Impossible"

if __name__ == '__main__':
    main()
