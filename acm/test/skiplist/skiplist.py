#coding=utf8
# ref: http://www.slideshare.net/iammutex/skip-list-9238027

import time
import random

class Node(object):
    def __init__(self, elem=None, next=None, down=None):
        self.elem = elem
        self.next = next
        self.down = down

    def __repr__(self):
        return '%s(%r)' % (self.__class__.__name__, self.elem)

    def items(self):
        ret = []
        row = []
        p = self
        while p:
            row.append(p.elem)
            p = p.next
        ret.append(row)
        if self.down:
            ret.extend(self.down.items())
        return ret

class SortedLinkedList(object):
    def __init__(self):
        self.head = Node()

    def find_prev(self, elem):
        """
            return the element proceeding either
                * the element containing x
                * the smallest element with a key larger than x
        """
        p = self.head
        while p.next and p.next.elem < elem:
            p = p.next
        return p
    
    def find(self, elem):
        return self.find_prev(elem).next

    def insert(self, elem):
        p = self.find_prev(elem)
        cur = Node(elem, p.next);
        p.next = cur

    def delete(self, elem):
        p = self.find_prev(elem)
        if p.next and p.next.elem == elem:
            p.next = p.next.next
            return True

    def items(self):
        ret = []
        p = self.head
        while (p.next):
            p = p.next
            ret.append(p.elem)
        return ret

class SkipList(object):
    def __init__(self):
        self.top = Node()
        self.level = 1

    def _find_prev(self, elem):
        ret = []
        p = self.top
        while True:
            while p.next and p.next.elem < elem:
                p = p.next
            ret.append(p)
            if p.down:
                p = p.down
            else:
                break
        return ret

    def find(self, elem):
        return self._find_prev(elem)[-1].next

    def gen_level(self):
        k = 1
        while k <= self.level and random.randint(0, 1) == 1:
            k += 1
        return k
    
    def insert(self, elem):
        k = self.gen_level()
        prev_list = self._find_prev(elem)
        down = None
        p = prev_list[-1]
        if p.next and p.next.elem == elem:
            return False
        else:
            for p in reversed(prev_list):
                cur = Node(elem, p.next, down)
                p.next = cur
                down = cur
                k -= 1
                if k == 0:
                    break
            if k:
                l = Node()
                cur = Node(elem, None, down)
                l.next = cur
                l.down = self.top
                self.top = l
                self._update_level(1)
            return True

    def delete(self, elem):
        prev_list = self._find_prev(elem)
        deleted = False
        for p in reversed(prev_list):
            if p.next and p.next.elem == elem:
                if not deleted:
                    deleted = True
                p.next = p.next.next
        while not self.top.next and self.top.down:
            self.top = self.top.down
            self._update_level(-1)
        return deleted

    def _update_level(self, add):
        self.level += add
        print "level add %d, cur_level = %d" % (add, self.level)

    def items(self):
        return self.top.items()

if __name__ == "__main__":
    s1 = SortedLinkedList()
    s1.insert(3)
    s1.insert(2)
    s1.insert(-1)
    assert s1.items() == [-1,2,3]
    s1.delete(-1)
    assert s1.items() == [2,3]
    s1.insert(-1)
    assert s1.items() == [-1,2,3]

    s2 = SortedLinkedList()
    start = time.time()
    times = 100
    for i in xrange(times):
        s2.insert(random.randint(1, 1000000))
    e = ((time.time()) - start) * 1000
    print "sorted linked list random insert %d cost %s ms" % (times, e)
    
    start = time.time()
    for i in xrange(times):
        s2.delete(random.randint(1, 1000000))
    e = ((time.time()) - start) * 1000
    print "sorted linked list random delete %d cost %s ms" % (times, e)

    s3 = SkipList()
    s3.insert(1)
    s3.insert(3)
    s3.insert(-1)
    s3.insert(4)
    s3.insert(4)
    s3.insert(4)
    s3.insert(4)
    s3.insert(4)
    print s3.items()
    s3.delete(4)
    print s3.items()

    start = time.time()
    times = 100
    for i in xrange(times):
        s3.insert(random.randint(1, 50))
    e = ((time.time()) - start) * 1000
    print "skiplist random insert %d cost %s ms, level = %d" % (times, e, s3.level)

    times = 1000
    start = time.time()
    for i in xrange(times):
        s3.delete(random.randint(1, 50))
    e = ((time.time()) - start) * 1000
    print "skiplist random delete %d cost %s ms, level = %d" % (times, e, s3.level)
