from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def main():
    t = read_ints()[0]
    for i in xrange(t):
        cas = i + 1
        n = read_ints()[0]

        flag = True
        arr = []
        last_black_line = -1
        for i in xrange(n):
            line = raw_input().strip()
            if '#' in line:
                start = line.find('#')
                end = line.rfind('#')
                arr.append((start, line[start:end+1]))
                if last_black_line != -1 and last_black_line + 1 != i:
                    flag = False
                last_black_line = i
        
        sz = len(arr)
        start = arr[0][0]
        for l in arr:
            if not flag:
                break
            if len(l[1]) != sz or l[0] != start:
                flag = False
            if '.' in l[1]:
                flag = False

        print "Case #%d: %s" % (cas,  "YES" if flag else "NO")

if __name__ == '__main__':
    main()
