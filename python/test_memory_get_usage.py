#coding=utf8

import unittest
import resource

def memory_usage_linux():
    """Memory usage of the current process in kilobytes.
        ref: http://stackoverflow.com/questions/897941/python-equivalent-of-phps-memory-get-usage
    """
    status = None
    result = {'peak': 0, 'rss': 0}
    try:
        # This will only work on systems with a /proc file system
        # (like Linux).
        status = open('/proc/self/status')
        for line in status:
            parts = line.split()
            key = parts[0][2:-1].lower()
            if key in result:
                result[key] = int(parts[1])
    finally:
        if status is not None:
            status.close()
    return result

def memory_usage():
    return resource.getrusage(resource.RUSAGE_SELF).ru_maxrss;

class Test_memory_usage(unittest.TestCase):
    def test1(self):
        l = []
        for i in range(1, 1000000):
            l.append('abcdefg')
            if len(l) % 100000 == 0:
                print "len = %d, memory usage = %.2f MB" % (len(l),  memory_usage() / 1024 / 1024)
                print "len = %d, memory usage = %.2f MB" % (len(l),  memory_usage() / 1024 / 1024)

        pass
    def test2(self):
        pass

if __name__ ==  "__main__":
    unittest.main()
