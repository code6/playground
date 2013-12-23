#coding=utf8

def islegal(n):
    if '0' in str(n):
        return False
    add = 0
    mul = 1
    for ch in str(n):
        dig = int(ch)
        add += dig
        mul *= dig
    if mul > add:
        return False
    return True

def f(n):
    ret = n
    while not islegal(ret):
        ret += n
    return ret

def test():
    for i in xrange(100):
        if i % 10 == 0:
            continue
        print i, f(i)

if __name__ == "__main__":
    test()
