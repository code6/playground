#coding=utf8

import random

def find(x, parent):
    if x == parent[x]:
        return x
    else:
        v = find(parent[x], parent)
        parent[x] = v
        return v

def randomTree(n):
    V = []
    parent = {}
    for i in xrange(n):
        parent[i + 1] = i + 1
    for i in xrange(n - 1):
        while True:
            ix = random.randint(1, n)
            iy = random.randint(1, n)
            fx = find(ix, parent)
            fy = find(iy, parent)
            if ix == iy or fx == fy:
                continue
            V.append((ix, iy))
            parent[fx] = fy

    return V

if __name__ == "__main__":
    print randomTree(3)
