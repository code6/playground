#coding=utf8

fs = []

def gen_for_1(L):
    if L 

def gen_fs():
    fs = [1, 4, 9, 121, 484]
    for L in range(3, 51):
        gen_for_1(L)
        gen_for_2(L)

def input():
    line = raw_input()
    A, B = line.strip().split(' ')

def calc(n):
    ret = 0
    for i in fs:
        if i < n:
            ret += 1
    return ret

def process(cas):
    ans = calc(B) - calc(A - 1)
    print "Case #%d: %d" % (cas, ans)

def run(cas):
    input()
    process(cas)

if __name__ == "__main__":
    gen_fs()
    T = int(raw_input())
    for cas in range(1, T + 1):
        run(cas)
