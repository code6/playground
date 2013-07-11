#coding=utf8
import os, sys
reload(sys)
sys.setdefaultencoding('utf-8')

import urllib2

line="http://www.paoshuba.com/Book/10098/Index.html"
req = urllib2.Request(line)
res = urllib2.urlopen(req)
content = res.read()
res.close()

c = content.decode('gbk', 'ignore')


#print c
print line


print "aa"
if c.find(u'至尊股神')==-1:
       print 'not find it!'
else:
       print 'find it'
