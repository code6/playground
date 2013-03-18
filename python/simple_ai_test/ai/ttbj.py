#coding=utf8

import sys
import time
import random

while True:
    cmd = sys.stdin.readline().strip()
    if cmd == "GUESS":
        key = random.randint(1, 1000)
        sys.stdout.write("%s\n" % key)
        sys.stdout.flush()
    elif cmd == "END":
        break

