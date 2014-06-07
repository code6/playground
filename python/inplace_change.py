#coding=utf8


def swap(arr, x, y):
    tmp = arr[x]
    arr[x] = arr[y]
    arr[y] = tmp
    print "after swap %d %d, arr = %s" % (x, y, arr)

def inplace_swap(arr):
    n = len(arr)
    assert n % 2 == 0
    half = n / 2
    if half > 1:
        d = half 
        for p in xrange(half - 1):
            x1 = p + 1
            y1 = x1 + d - 1
            y2 = n - 2 - p
            x2 = y2 - d + 1
            d -= 1
            print x1, y1, x2, y2, n, d
            swap(arr, x1, y1)
            if x2 != x1 and y2 != y1:
                swap(arr, x2, y2)
    return arr

def gen(n):
    arr = []
    for i in xrange(n):
        arr.append('a%d' % i)
    for i in xrange(n):
        arr.append('b%d' % i)
    return arr


if __name__ == "__main__":
    arr = gen(5)
    print arr
    inplace_swap(arr)
    print arr

