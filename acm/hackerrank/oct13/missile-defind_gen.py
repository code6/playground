#coding=utf8
import random
t = 100
name = "missile.in"

of = open(name, "w")
print >> of, t
for i in range(t):
    n = random.randint(1, 1000)
    print >> of, n
    for j in range(n):
        x = random.randint(0, 1000)
        y = random.randint(0, 1000)
        print >> of, x, y

