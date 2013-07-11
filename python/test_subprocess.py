#coding=utf8

import subprocess


p = subprocess.Popen("ls ")
p.wait()
print "return code=", p.returncode
