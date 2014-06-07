n = int(raw_input())

def squ_root(n):
    sr = int(n ** (1/2.0))
    for i in xrange(6):
        val = sr +  3 - i
        if val ** 2 == n:
            return val
    return -1

ret = []

for k in xrange(0, 64):
    a = 1
    a2 = a * 2
    b = (2 ** (k + 1)) - 3
    c = -2 * n
    delta = b * b - 4 * a * c
    sr = squ_root(delta)
    if sr != -1:
        v1 = sr - b
        v2 = -sr - b
        if v1 >= 0 and v1 % a2 == 0 and ((v1 / a2) % 2 == 1):
            tmp = v1 / a2 * (2 ** k)
            ret.append(tmp)
        if v2 >= 0 and v2 % a2 == 0 and ((v2 / a2) % 2 == 1):
            tmp = v2 / a2 * (2 ** k)
            ret.append(tmp)

ret = list(set(ret))
ret.sort()

if ret:
    for i in ret:
        print i
else:
    print -1
