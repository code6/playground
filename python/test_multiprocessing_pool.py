#coding=utf8

from multiprocessing import Pool, Pipe


def target(one_dict):
    one_dict['add'] = 1
    return one_dict

pool = Pool(2)
class Base(object):
    def __init__(self):
        self.d = {'a':{'a1':1}, 'b':{'b1':2}, 'c':{'c1':3}}
        dd = {}
        dd['xx'] = pool.apply_async(target, (self.d['b'], ))
        self.d['b'] = dd['xx'].get()
        del dd['xx']
        print self.d
        print dd

a = Base()
#a.target(a.d['b'])
