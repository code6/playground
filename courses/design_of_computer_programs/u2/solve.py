#coding=utf8

from __future__ import division
import string, re
import itertools
import time

def solve(formula):
    for f in fill_in(formula):
        if valid(f):
            return f


def fill_in(formula):
    letters = ''.join(set(re.findall('[A-Z]', formula)))
    for digits in itertools.permutations('1234567890', len(letters)):
        table = string.maketrans(letters, ''.join(digits))
        yield formula.translate(table)

def valid(f):
    try:
        return not re.search(r'\b0[0-9]', f) and eval(f) is True
    except ArithmeticError:
        return False

def timecall(func, *arg):
    before = time.time()
    func(*arg)
    after = time.time()
    print "time elipse = ", after - before
    

if __name__ == "__main__":
    timecall(solve, "A + B == C")
    
