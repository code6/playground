#coding=utf8

import os
import signal
from subprocess import Popen

os.setpgrp() # create new process group, become its leader
popen = Popen(, shell=True)
from time import sleep

sleep(1)
#popen.terminate()
os.killpg(0, signal.SIGKILL) # kill all processes in my group
