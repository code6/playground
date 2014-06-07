#coding=utf8

from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def gen(n, cn, tn):
    ret = tn[0]
    for i in xrange(cn):
        if ret[-1] == "A":
            ret +="C"
        else:
            ret += "AC"
    if len(ret) > n:
        return ""
    if len(ret) == n and ret[-1] != tn[1]:
        return ""

    if len(ret) < n:
        for i in xrange(n - len(ret) - 1):
            ret += "O"
        if ret[-1] == "A" and tn[1] == "C":
            return ""
        ret += tn[1]
    return ret

def calc(k, x, cn, tn, cm, tm):
    arr = [(cn, tn), (cm, tm)]
    for i in xrange(k):
        if i < 2:
            continue
        cn, tn = arr[i-2]
        cm, tm  = arr[i-1]
        arr.append((cn + cm + ((tn[1]+tm[0]) =="AC") , tn[0]+tm[1]))
        if arr[-1][0] > x:
            return -1
    return arr[k-1][0]

def solve(k, x, n, m):
    tylist = ["AA", "AC", "CA", "CC"]
    for cn in xrange(n/2 + 1):
        for cm in xrange(m/2 + 1):
            for tn in tylist:
                for tm in tylist:
                    sn = gen(n, cn, tn)
                    sm = gen(m, cm, tm)
                    if not sn or not sm:
                        continue
                    cnt = calc(k, x,  cn, tn, cm, tm)
                    if cnt == x:
                        return "\n".join([sn, sm])
    return "Happy new year!"

def main():
    k,x,n,m = read_ints()
    print solve(k, x, n, m)

if __name__ == '__main__':
    main()

#####
#50 1000000000 100 100
#ACA
#CAC
#ACACAC
#CAC ACACAC
#ACACACCACACACAC 7
# 5 7 3  3
