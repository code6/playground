#coding=utf-8

import bisect

class BNode(object):
    def __init__(self, keylist = None, nextlist = None):
        if keylist is None:
            keylist = []
        if nextlist is None:
            nextlist = []
        self.is_leaf = False
        self._keylist = keylist
        self._nextlist = nextlist

    @property
    def key_size(self):
        return len(self._keylist)

    def get_min_key(self):
        return self._keylist[0] if self._keylist else None

    def insert(self, key, val):
        pos = bisect.bisect_left(self._keylist, key)
        self._keylist.insert(pos, key)
        self._nextlist.insert(pos, val)

    def find(self, key):
        for pos, cur_key in enumerate(self._keylist):
            if key < cur_key:
                return self._nextlist[pos]
        return self._nextlist[-1]

    def __str__(self):
        return "Interal Node(keys=%s, next=%s)" % (self._keylist, [id(ne) for ne in self._nextlist])

class BLeafNode(object):
    def __init__(self, keylist = None, nextlist = None, nextptr = None):
        if keylist is None:
            keylist = []
        if nextlist is None:
            nextlist = []
        self.is_leaf = True
        self._keylist = keylist
        self._nextlist = nextlist
        self._nextptr = nextptr

    @property
    def key_size(self):
        return len(self._keylist)

    def get_min_key(self):
        return self._keylist[0] if self._keylist else None

    def find(self, key):
        for pos, cur_key in enumerate(self._keylist):
            if key == cur_key:
                return self._nextlist[pos]

    def contain(self, key):
        return key in self._keylist

    def insert(self, key, val):
        pos = bisect.bisect_left(self._keylist, key)
        self._keylist.insert(pos, key)
        self._nextlist.insert(pos, val)

    def update(self, key, val):
        if self.contain(key):
            pos = self._keylist.index(key)
            self._nextlist[pos] = val

    def split_half(self):
        half_len = (len(self._keylist) + 1) / 2
        new_node = BLeafNode(self._keylist[half_len:], 
                self._nextlist[half_len:], 
                self._nextptr)
        self._nextptr = new_node
        self._keylist = self._keylist[:half_len]
        self._nextlist = self._nextlist[:half_len]

        return self, new_node

    def __iter__(self):
        cur_node = self
        while cur_node:
            for pos, cur_key in enumerate(cur_node._keylist):
                yield cur_key, cur_node._nextlist[pos]
            cur_node = cur_node._nextptr

    def __str__(self):
        return "Leaf Node(id=%s, keys=%s, next=%s, nextptr=%s)" % (id(self), self._keylist, self._nextlist, id(self._nextptr))

class BPlusTree(object):
    BRANCH = BNode
    LEAF = BLeafNode

    def __init__(self, order):
        self.order = order
        self.root = BLeafNode()

    def search_leaf(self, key, node = None):
        if not node:
            node = self.root
        while not node.is_leaf:
            node = node.find(key)
        return node

    def search(self, key, node = None):
        return self.search_leaf(key, node).find(key)
    
    def need_split(self, node):
        print "at need_split", node
        return node.key_size > self.order

    def insert(self, key, val):
        stack = []
        node = self.root
        while not node.is_leaf:
            stack.append(node)
            node = node.find(key)
        stack.append(node)

        if node.contain(key):
            node.update(key, val)
            return

        node.insert(key, val)
        while stack:
            node = stack.pop()
            if self.need_split(node):
                node, node1 = node.split_half()
                if not stack:
                    stack.append(BNode(nextlist = [node]))
                    if node == self.root:
                        self.root = stack[-1]
                stack[-1].insert(node1.get_min_key(), node1)
            else:
                break


    def delete(self, key):
        pass

def test_insert():
    tr = BPlusTree(3)
    for i in range(5):
        print "insert %d" % i
        tr.insert(i, 'val%d' % i)
        min_leaf = tr.search_leaf(-10000)
        print min_leaf
        for k, v in min_leaf:
            print k, v

if __name__ == '__main__':
    test_insert()

