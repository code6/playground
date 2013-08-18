#coding=utf8
'''
   doubly linked list, translate from
   go/src/pkg/container/list/list.go
'''
import time

class Node(object):
    def __init__(self, elem = None, prev = None, next = None):
        self.elem = elem
        self.next = next
        self.prev = prev

    def __repr__(self):
        return '%s(%r)' % (self.__class__.__name__, self.elem)

class LinkedList(object):
    def __init__(self):
        self.n = 0
        self.first = self.last = None

    def size(self):
        return self.n

    def front(self):
        if self.n == 0:
            return None
        return self.first

    def back(self):
        if self.n == 0:
            return None
        return self.last

    def remove(self, node):
        """
        assume node is in the list
        """
        if node.prev is not None:
            node.prev.next = node.next
        else:
            self.first = node.next
        if node.next is not None:
            node.next.prev = node.prev
        else:
            self.last = node.prev
        node.prev = node.next = None
        self.n -= 1
        return node

    def move_to_front(self, node):
        if node != self.first:
            self.remove(node)
            self._insert_front(node)

    def move_to_back(self, node):
        if node != self.last:
            self.remove(node)
            self._insert_back(node)

    def push_front(self, elem):
        node = Node(elem, None, None)
        self._insert_front(node)
        return node

    def push_back(self, elem):
        node = Node(elem, None, None)
        self._insert_back(node)
        return node

    def _insert_front(self, node):
        if self.n == 0:
            self.first = self.last = node
        else:
            node.prev = None
            node.next = self.first
            self.first.prev = node
            self.first = node
        self.n += 1
            
    def _insert_back(self, node):
        if self.n == 0:
            self.first = self.last = node
        else:
            node.prev = self.last
            node.next = None
            self.last.next = node
            self.last = node
        self.n += 1

    def __iter__(self):
        node = self.first
        while node is not None:
            yield node
            node = node.next

    def __repr__(self):
        return str([node for node in self])

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

class Profiler(object):
    def __init__(self, size):
        self.size = size
        self.list = None
        self.linked_list = None
        self.sw_create_list = Stopwatch()
        self.sw_create_linked_list = Stopwatch()
        self.sw_pop_list = Stopwatch()
        self.sw_pop_linked_list = Stopwatch()
        
    def create_list(self):
        self.sw_create_list.start()
        self.list = [i for i in range(self.size)]
        self.sw_create_list.stop()
    
    def create_linked_list(self):
        self.sw_create_linked_list.start()
        self.linked_list = LinkedList()
        for value in self.list:
            self.linked_list.push_back(value)
        self.sw_create_linked_list.stop()
    
    def pop_list(self):
        self.sw_pop_list.start()
        for i in range(self.size):
            del self.list[0]
        self.sw_pop_list.stop()
    
    def pop_linked_list(self):
        self.sw_pop_linked_list.start()
        for i in range(self.size):
            node = self.linked_list.back()
            self.linked_list.remove(node)
            del node
        self.sw_pop_linked_list.stop()
        
    def report(self):
        print("%6s %10d" % ("Size", self.size))
        print("%6s %10s %10s %10s" % ("Type", "Create", "Pop", "Total")) 
        print("%6s %10.2f %10.2f %10.2f" % ("List", self.sw_create_list.duration(), \
                self.sw_pop_list.duration(), self.sw_create_list.duration() + self.sw_pop_list.duration()))
        print("%6s %10.2f %10.2f %10.2f" % ("Linked", self.sw_create_linked_list.duration(), \
                self.sw_pop_linked_list.duration(), self.sw_create_linked_list.duration() + \
                self.sw_pop_linked_list.duration()))
        print

        
    def run(self):
        self.create_list()
        self.create_linked_list()
        self.pop_list()
        self.pop_linked_list()
        self.report()
   
if __name__ == '__main__':
    Profiler(1000).run()
    Profiler(2000).run()
    Profiler(5000).run()
    Profiler(10000).run()
    Profiler(20000).run()
    Profiler(50000).run()
    Profiler(100000).run()
    print "Complete."

