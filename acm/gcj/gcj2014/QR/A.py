from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def format_ans(ans):
    if ans == -1:
        return "Bad magician!"
    if ans == -2:
        return "Volunteer cheated!"
    return ans

def main():
    t = read_ints()[0]
    for cas in xrange(t):
        ans1 = read_ints()[0]
        rows1 = []
        for i in xrange(4):
            row = set(read_ints())
            rows1.append(row)
        ans2 = read_ints()[0]
        rows2 = []
        for i in xrange(4):
            row = set(read_ints())
            rows2.append(row)
        v = rows1[ans1-1].intersection(rows2[ans2-1])
        if len(v) == 1:
            ans = list(v)[0]
        elif len(v) > 1:
            ans = -1 
        else:
            ans = -2
        print "Case #%d: %s" % (cas + 1, format_ans(ans))

if __name__ == '__main__':
    main()
