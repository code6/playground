from collections import Counter, defaultdict
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def legal(a, b):
    for i in xrange(len(a)):
        if a[i] > b[i]:
            return False
    return True

def change(arr):
    return arr

def main():
    ok_arr = []
    for i in xrange(350):
        if i:
            ok = True
            for j in xrange(i):
                if j > 1 and i% j ==0 and i / j >= 50:
                    ok = False
                    break
            if ok:
                ok_arr.append(i)
    print len(ok_arr), ok_arr

    t = read_ints()[0]
    for i in xrange(t):
        cas = i + 1
        n, k = read_ints()
        arr = read_ints()
        arr.sort()
        before = sum(arr)

        min_arr = [0] + [k] * (n-1)
        if legal(arr, min_arr):
            after = sum(min_arr)
        else:
            for i in xrange(n):
                arr[i] = ((max(1, arr[i]) -1)  / k + 1)
            arr = change(arr)
            after = sum(arr) * k

        ans = after - before
        print "Case #%d: %s" % (cas,  ans)

if __name__ == '__main__':
    main()
