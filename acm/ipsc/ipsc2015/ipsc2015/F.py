from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

MOD = 10 ** 9 + 7

def find(x, parent):                                                                                                                                          
    if x == parent[x]:                                                                                                                                        
        return x                                                                                                                                              
    else:                                                                                                                                                     
        v = find(parent[x], parent)                                                                                                                           
        parent[x] = v                                                                                                                                         
        return v 

def merge(a, b, parent):
    a = find(a, parent)
    b = find(b, parent)
    if a != b:
        parent[a] = b
        return True
    return False

def main():
    t = read_ints()[0]
    for cas in xrange(t):
        raw_input()
        n, q = read_ints()
        parent = [{}, {}]
        for i in xrange(n):
            parent[0][i] = i
            parent[1][i] = i
        ans = 0
        wei = 0
        for i in xrange(q):
            v, a, b = read_ints()
            v -= 1
            a -= 1
            b -= 1
            a = find(a, parent[v])
            b = find(b, parent[v])
            if a != b:
                va = [j for j in xrange(n) if find(j, parent[v]) == a]
                vb = [j for j in xrange(n) if find(j, parent[v]) == b]
                merge(a, b, parent[v])
                for x in va:
                    for y in vb:
                        if find(x, parent[1-v]) == find(y, parent[1-v]):
                            wei += 1
            ans = (ans + wei * (i + 1)) % MOD
        print ans

if __name__ == '__main__':
    main()
