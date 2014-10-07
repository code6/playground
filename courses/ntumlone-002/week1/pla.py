#coding=utf8

import operator
import random
import copy

EPS = 1e-9

def dot_product(v1, v2):
    return sum(map(operator.mul, v1, v2))

def add(v1, v2):
    return map(operator.add, v1, v2)

def load_data_from_file(f):
    """
        load pla data from file (xn, yn)
        xn = (x1, x2, x3, x4)
    """
    result = []
    for line in open(f, "r").readlines():
        data = [float(v.strip()) for v in line.split(' ') if v.strip()]
        x, y = data[:4], data[-1]
        x.append(1.0)
        result.append((x, y))
    return result

def mistake(w, data):
    ret = 0
    for (xn, yn) in data:
        val = dot_product(w, xn) * yn
        if val < -EPS or (abs(val) < EPS):
            ret += 1
    return ret

def pocket(input_data, shuffle=False, update_limit=50):
    data = copy.deepcopy(input_data)
    if shuffle:
        random.shuffle(data)
    w = [0.0] * len(data[0][0])
    update_cnt = 0
    while update_cnt <= update_limit:
        has_update = False
        for (xn, yn) in data:
            val = dot_product(w, xn) * yn
            if val < -EPS or (abs(val) < EPS):
                w_next = add(w, [yn * v for v in xn])
                if mistake(w, data) > mistake(w_next, data):
                    update_cnt += 1
                    has_update = True
                    w = w_next
        if not has_update:
            break
    return w, update_cnt

def pla(input_data, shuffle=False, update_limit=-1):
    """
    pla with four dims data
    """
    data = copy.deepcopy(input_data)
    if shuffle:
        random.shuffle(data)
    w = [0.0] * len(data[0][0])
    update_cnt = 0
    while True:
        has_update = False
        for (xn, yn) in data:
            val = dot_product(w, xn) * yn
            if val < -EPS or (abs(val) < EPS  and yn > 0):
                #print update_cnt, w, xn, yn, val
                update_cnt += 1
                has_update = True
                w = add(w, [0.5 * yn * v for v in xn])
                if update_limit != -1 and update_cnt >= update_limit:
                    break
        if not has_update:
            break
        if update_limit != -1 and update_cnt >= update_limit:
            break
    return w, update_cnt

if __name__ == "__main__":
    T = 2000
    C = 0.0
    #for idx in range(T):
    #     w, cnt = pla(load_data_from_file("hw1_15_train.dat"), shuffle=True)
    #     print idx, w, cnt
    #     C += cnt
    #print 1.0 * C / T
    test_data = load_data_from_file("hw1_18_test.dat")
    for idx in range(T):
        #w  = pocket(load_data_from_file("hw1_18_train.dat"), shuffle=True, update_limit=50)
        w, update_cnt = pla(load_data_from_file("hw1_18_train.dat"), shuffle=True, update_limit=100)
        C += 1.0 * mistake(w, test_data) / len(test_data)
        #print idx, w, C, update_cnt
    print 1.0 * C / T
