from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def get_insult():
    ret = []
    n = read_ints()[0]
    for i in xrange(n):
        w, s = [v for v in raw_input().strip().split(' ') if v]
        s = int(s)
        ret.append((w,s))
    ret = sorted(ret, key=lambda d: d[1])
    return ret

def main():
    insults = []
    insults.append(get_insult())
    insults.append(get_insult())
    insults.append(get_insult())
    mm = {}
    for i in xrange(len(insults)):
        for v in insults[i]:
            mm[v[0]] = v[1]

    ans = {}
    n = read_ints()[0]
    for i in xrange(n):
        a,b,c = [v for v in raw_input().strip().split(' ') if v]
        cost = mm[a] + mm[b] + mm[c] + 1
        if not cost in ans:
            ans[cost] = []
        ans[cost].append(i)
    
    le = {}
    for u in insults[0]:
        for v in insults[1]:
            cost = u[1] + v[1]
            if not cost in le:
                le[cost] = []
            le[cost] = [(u[0], v[0])]
    
    output = {}
    for cost, arr in ans.iteritems():
        need = len(arr)
        for u in insults[2]:
            if cost <= u[1] or not need:
                break
            left = cost - u[1]
            if not left in le:
                continue
            for v in le[left]:
                need -= 1
                qid = arr[need]
                res = "%s %s %s" % (v[0], v[1], u[0])
                output[qid] = res
                if not need:
                    break

    for i in xrange(n):
        print output[i]

if __name__ == '__main__':
    main()
