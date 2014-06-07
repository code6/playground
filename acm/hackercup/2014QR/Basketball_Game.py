from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def main():
    t = read_ints()[0]
    for i in xrange(t):
        cas = i + 1
        n, m, p = read_ints()
        players = []
        for i in xrange(n):
            name, shot, height = raw_input().split()
            shot = int(shot)
            height = int(height)
            d = {
                'name': name,
                'shot': shot,
                'height':height,
                'time' : 0,
                'number' : -1,
            }
            players.append(d)
        players = sorted(players, key=lambda d: d['shot'] * 100000 + d['height'])[::-1]
        for i in xrange(n):
            players[i]['number'] = i
        teams = [players[::2], players[1::2]]
        for r in xrange(m):
            for t in teams:
                for i in xrange(p):
                    t[i]['time'] += 1
                if len(t) > p:
                    t[:p] = sorted(t[:p], key=lambda d: d['time'] * 100000 + d['number'])
                    t[p:] = sorted(t[p:], key=lambda d: d['time'] * 100000 + d['number'])
                    t[p -1], t[p] = t[p], t[p-1]

        ans = []
        for t in teams:
            for d in t[:p]:
                ans.append(d['name'])
        res = " ".join(sorted(ans))
        print "Case #%d: %s" % (cas,  res)

if __name__ == '__main__':
    main()
