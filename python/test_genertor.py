def test():
    print(yield)
    print 1
    print (yield)
    print 2

for l in test():
    pass

s = test()
s.send(None)
s.send('x')
s.send('y')

