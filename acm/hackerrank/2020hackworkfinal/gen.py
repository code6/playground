#coding=utf8

from random import randint

def gen_best_sum(fn):
    f = open(fn, "w")
    t = 20 #randint(1, 10)
    print >> f, t
    for i in xrange(t):
        n = randint(1, 1000)
        print >> f, n
        for j in xrange(n):
            print >> f, randint(-1000000, 1000000), 
        print >> f
        for j in xrange(n):
            print >> f, randint(-1000000, 1000000), 
        print >> f

def gen_almost_equal(fn):
    f = open(fn, "w")
    n = 10 #randint(2, 10 ** 3)
    k = 2 #randint(0, 10 ** 9)
    print >> f, n, k
    for i in xrange(n):
        h = randint(0, 10)#10 ** 9)
        print >> f, h,
    print >> f
    q = randint(1, 10 ** 3)
    print >> f, q
    for i in xrange(q):
        l = randint(0, n - 2)
        r = randint(l, n - 1)
        print >> f, l , r

if __name__ == "__main__":
    #gen_best_sum("best_sum.in")
    gen_almost_equal("almost_equal.in")

