#coding=utf8
'''
   doubly linked list with sentinal
   origin: https://github.com/shenfeng/gocode/blob/user_data/src/thrift_proxy/user_data/lru_cache.py
'''

class Element(object):
    def __init__(self, value = None, prev = None, next = None):
        self.value = value
        self.next = next
        self.prev = prev

    def __repr__(self):
        return '%s(%r)' % (self.__class__.__name__, self.value)


class LinkedList(object):
    def __init__(self):
        root = Element()
        root.prev = root.next = root
        self.root = root

    def remove(self, e):
        e.prev.next = e.next
        e.next.prev = e.prev
        return e

    def push_front(self, e):
        n = self.root.next
        n.prev = e
        self.root.next = e
        e.next = n
        e.prev = self.root

    def move_to_front(self, e):
        e = self.remove(e)
        self.push_front(e)

    def back(self):
        p = self.root.prev
        if p != self.root:
            return p

    def items(self):
        r = []
        node = self.root.next
        while  node != self.root:
            r.append(node.value)
            node = node.next
        return r
    
    def __repr__(self):
        return ",".join(str(v) for v in self.items())

if __name__ == "__main__":
    l = LinkedList()
    l.push_front(Element(10))
    l.push_front(Element(11))
    l.push_front(Element(12))
    print l
