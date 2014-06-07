from collections import Counter, defaultdict
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

def conv_percent(v):
    return (int)(float(v) * 1000 + 0.5)

def main():
    t = read_ints()[0]
    for i in xrange(t):
        cas = i + 1
        k,  ps, pr, pi, pu, pw, pd, pl = raw_input().split()
        k = int(k)
        ps, pr, pi, pu, pw, pd, pl  = float(ps), float(pr), conv_percent(pi), conv_percent(pu), float(pw), conv_percent(pd), float(pl)

        ans = 0.0

        S = defaultdict(float)
        S[(0, 0, pi)] = 1.0
        while S:
            NS = defaultdict(float)
            for state, prob in S.iteritems():
                x, y, conv_prob_sun = state
                prob_sun = (float)(conv_prob_sun / 1000.0)

                #win
                win_prob = (prob_sun * ps + (1.0 - prob_sun) * pr) * prob
                nx, ny, next_prob =  x + 1, y, win_prob
                if (nx == k or ny == k):
                    if nx == k:
                        ans += next_prob
                else:
                    NS[(nx, ny, min(1000, conv_prob_sun + pu))] += next_prob * pw
                    NS[(nx, ny, conv_prob_sun)] += next_prob * (1 - pw)

                #fail
                fail_prob = (1.0 - (prob_sun * ps + (1 - prob_sun) * pr)) * prob
                nx, ny, next_prob = x, y + 1, fail_prob
                if (nx == k or ny == k):
                    if nx == k:
                        ans += next_prob
                else:
                    NS[(nx, ny, max(0, conv_prob_sun - pd))] += next_prob * pl
                    NS[(nx, ny, conv_prob_sun)] += next_prob * (1 - pl)
            S = NS

        print "Case #%d: %.6f" % (cas,  ans)

if __name__ == '__main__':
    main()
