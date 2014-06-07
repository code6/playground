#coding=utf8

import os
import sys
from subprocess import Popen, PIPE

cmd = 'env LC_CTYPE=C tr -dc "a-zA-Z0-9-_\$\?" < /dev/urandom | fold -w 655 | head -n 1 > test.tmp && cat test.tmp'
print cmd
p = Popen(cmd, shell=True, stdout=PIPE,stderr=None, stdin=None)
p.wait()
