#coding=utf8
import string

table = string.maketrans('ABC', '123')

f = 'A + B == C'
print eval(f.translate(table))
