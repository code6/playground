#coding=utf8

import sys
import time
import random

mi = 0
mx = 1000
while True:
    cmd = sys.stdin.readline().strip()
    if cmd == "GUESS":
        key = random.randint(mi, mx)
        sys.stdout.write("%s\n" % key)
        sys.stdout.flush()
    elif cmd == "END":
        break
    else:
        who, _, val, res = cmd.split(' ')
        val = int(val)
        if res == "SMALL":
            mi = max(mi, val + 1)
        else:
            mx = min(mx, val - 1)

