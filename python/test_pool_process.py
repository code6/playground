#coding=utf8


import os
import sys
import multiprocessing
import subprocess
from test_nodaemon_pool import MyPool
import time

def another_func():
    print >> sys.stderr, " at another_func "

def another_func_1(prev):
    print >> sys.stderr, " at another_func "
    prev.send("hello")
    exit(0)

def test_pool_process():
    print >> sys.stderr, " at  test_pool_process "
    p = subprocess.Popen("python raise15.py", shell=True)
    #p = subprocess.Popen("sleep 50", shell=True)
    p.wait()
    return 1
    p = multiprocessing.Process(
            target = another_func,
            )
    ret = 1
    p.start()
    p.join()
    #pmain, pret = multiprocessing.Pipe()
    #p = multiprocessing.Process(
    #        target=another_func_1,
    #        args = (pret)
    #        )
    #p.start()
    #p.join()
    #ret = pmain.recv()
    print >> sys.stderr, "another func return %s" % ret
    print >> sys.stderr, "after start"
    return 1


def main():
    p = multiprocessing.Pool(1)
    #p = MyPool(1)
    p.apply(test_pool_process)

main()
