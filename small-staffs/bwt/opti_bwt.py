#coding=utf-8

def shift(l, n):
    return l[n:] + l[:n]

def bwt(str):
    str += '\0'
    arr = []
    for i in range(len(str)):
        arr.append(str)
        str = shift(str, 1)
    arr.sort()
    ret = ''
    for s in arr:
        ret += s[-1]
    return ret

def inv_bwt(str):
    sz = len(str)
    arr = [""] * sz
    for i in range(sz):
        for j in range(sz):
            arr[j] = str[j] + arr[j]
        arr.sort()
    for s in arr:
        if s.endswith('\0'):
            return s[:-1]

if __name__ == "__main__":
    s = "abc11abc22abc33"
    print bwt(s)
    print inv_bwt(bwt(s))
