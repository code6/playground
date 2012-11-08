#coding=utf-8

import sys

answer_file = sys.argv[1]

lines = open(answer_file).read().strip().split('\n')
cnt = 0

for l in lines:
    print "at line ", cnt
    cnt += 1
    arr = set(int(v.strip()) for v in l.replace(',', ' ').replace(';', ' ').split(' ') if v.strip())
    for num in xrange(1, 127):
        if not num in arr:
            print "Number Not Found: ", num

