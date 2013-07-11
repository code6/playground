#coding=utf8

import subprocess

p = subprocess.Popen("ulimit -v 1; ls", shell=True)
p.wait()
