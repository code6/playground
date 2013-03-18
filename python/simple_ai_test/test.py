
#coding=utf8
import subprocess

p = subprocess.Popen(['sed', '-l', 's/a/x/g'],
                     stdout=subprocess.PIPE,
                     stdin=subprocess.PIPE)

p.stdin.write("abc\n")
print "Reading result:"
print p.stdout.readline()

p.stdin.write("cat\n")
print "Reading result:"
print p.stdout.readline()
