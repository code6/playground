#coding=utf8

import random

f = open("gs.in", "w")

t = random.randint(10, 20)
print >> f, t
for i in xrange(t):
    n = 1
    m = random.randint(1, 5)
    k = random.randint(n * m / 2, n * m)
    print >> f, n, m, k
    candi = "TD"
    for j in xrange(n):
        s = ""
        for w in xrange(m):
            if random.randint(1, 10) == 1:
                s += candi[random.randint(0,1)]
            else:
                s += "U"
        print >> f, s
