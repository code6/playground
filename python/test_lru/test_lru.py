#coding=utf8
'''
   lru cache test, translate from 
   https://github.com/shenfeng/gocode/blob/master/src/thrift_proxy/lru_cache.go
   Entry can be as simple as a tuple
'''

from linkedlist import LinkedList, Node
import time
import threading

class Entry(object):
    def __init__(self, key, value, expire):
        self.key = key
        self.value = value
        self.expire = expire

    def __repr__(self):
        return '(key = %r, value = %r, expire = %r)' % (self.key, self.value, self.expire)

class LRUCache(object):
    def __init__(self, capacity):
        self.init(capacity)

    def init(self, capacity):
        self.capacity = capacity
        self.table = {}
        self.data = LinkedList()
        self.hitcnt = self.misscnt = self.expirecnt = 0
        self.lock = threading.Lock()

    def stats(self):
        per = 1.0 * self.hitcnt / max(1, self.misscnt + self.expirecnt + self.misscnt);
        return "size = %d, hitcnt = %d, misscnt = %d, expirecnt = %d, hit per=%.4lf\n" % (
                len(self.table), self.hitcnt, self.misscnt, self.expirecnt, per)

    def delete(self, key):
        with self.lock:
            if key in self.table:
                node = self.table[key]
                self.data.remove(node)
                del self.table[key]
                return True

    def get(self, key):
        """
        get the cache value with specifiy key
        return None either key is not found or value is expired
        """
        with self.lock:
            if key in self.table:
                node = self.table[key]
                if node.elem.expire < time.time():
                    #expire
                    self.expirecnt += 1
                    self.data.remove(node)
                    del self.table[key]
                else:
                    self.hitcnt += 1
                    self.data.move_to_front(node)
                    return node.elem.value
            else:
                self.misscnt += 1

    def setex(self, key, seconds, value):
        with self.lock:
            expire = int(time.time()) + seconds
            if key in self.table:
                #already exists
                node = self.table[key]
                node.elem = Entry(key, value, expire)
                self.data.move_to_front(node)
            else:
                self._add(key, expire, value)

    def _add(self, key, expire, value):
        node = self.data.push_front(Entry(key, value, expire))
        self.table[key] = node 
        if len(self.table) > self.capacity:
            node = self.data.back()
            self.data.remove(node)
            del self.table[node.elem.key]

class Stopwatch(object):
    def __init__(self):
        self.__start = 0.0
        self.__stop = 0.0
        self.__duration = 0.0
    
    def start(self):
        self.__start = time.time()
        return self
    
    def stop(self):
        self.__stop = time.time()
        self.__duration = self.__stop - self.__start
        return self.__duration
    
    def duration(self):
        return self.__duration   

if __name__ == "__main__":
    cache = LRUCache(5)

    for i in xrange(5):
        key = i
        val = i * i
        second = 10
        cache.setex(key, second, val)
    print cache.data
    cache.setex(6, 10, 100)
    print cache.data
    for i in reversed(xrange(5)):
        cache.get(i)
    print cache.data
    for i in xrange(5):
        val = cache.get(i)
        if val:
            cache.delete(i)
    print cache.data
    print cache.stats()
    

    cache = LRUCache(100)
    for i in xrange(100):
        cache.setex("key-%s" % i, 10, "value-%s" % i)
    for i in xrange(100):
        v = cache.get("key-%s" % i)
        if not v:
            print "GET", i, "error"

    LOOP = 1000000

    # bench mark setex, about 300k per seconds on i7-3770K
    start = time.time()
    cache = LRUCache(20000)
    for i in xrange(LOOP):
        cache.setex("key-%s" % (i % 20000), 10, "value-%s" % i)
    e = (time.time() - start) * 1000
    print cache.stats()

    print "setex", LOOP, "takes time", e, "ms"

    # benchmark get, about 700k per seconds i7-3770K
    start = time.time()
    for i in xrange(LOOP):
        cache.get("key-%s" % (i % 2000))
    e = (time.time() - start) * 1000
    print cache.stats()
    print "get", LOOP, "takes time", e, "ms"

    from guppy import hpy

    h = hpy()
    print h.heap()

