#coding=utf8
import time

def getDataByOffset(out_file, offset, size):
    try:
        out_stream = open(out_file, "r")
        out_stream.seek(offset)
        ret = out_stream.read(size)
        out_stream = None
        return ret
    except:
        return ""

def cpfile(f, r):
    out_stream = open(r, "w")
    offset = 0
    batch = 1000
    while True:
        text = getDataByOffset(f, offset, batch)
        out_stream.write(text)
        l = len(text)
        offset += l
        time.sleep(.5)
        print "len = ", len(text)
        if l < batch:
            break

cpfile("fork_threading.py", "fork_threading.cp")

