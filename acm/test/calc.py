#coding=utf8

read_ints = lambda: map(int, raw_input().split())

#先假设没有正负号, 假设字符串合法
# 1 + (12 + 4)

# 提高, 有正负号怎么办呢?
#((1+2)*(-333+4)+1) * (-5)
# 1 * -5
# 1 * (-5)
# 1 - 5
# ((((-1))))

op_priority = ['(', ')', '+', '-', '*', '/']
def get_pri(op):
    return op_priority.index(op)

class Calc(object):
    def __init__(self):
        self.op_stack = []
        self.data_stack = []

    def run(self):
        if self.op_stack:
            s = "%s %s %s" % (self.data_stack[-2], self.op_stack[-1], self.data_stack[-1])
            self.data_stack = self.data_stack[:-2]
            self.op_stack = self.op_stack[:-1]
            self.data_stack.append(eval(s))
            return True
        else:
            return False

    def push_high(self, op):
        while self.op_stack and get_pri(self.op_stack[-1]) >= get_pri(op):
            self.run()
    
    def __str__(self):
        return "%s %s" % (self.op_stack, self.data_stack)

def calc(s):
    pos = 0
    length = len(s)
    calc = Calc()
    while pos < length: 
        c = s[pos]
        if c in ('*', '/', '+', '-') :
            calc.push_high(c)
            calc.op_stack.append(c)
        if c == '(':
            calc.op_stack.append(c)
        if c == ')':
            while calc.op_stack[-1] != '(':
                calc.run()
            calc.op_stack = calc.op_stack[:-1]
        if c.isdigit():
            num = "" 
            while pos < length and s[pos].isdigit():
                num += s[pos]
                pos += 1
            pos -= 1
            calc.data_stack.append(int(num))
        pos += 1
    while calc.run():
        pass
    return calc.data_stack[0]

def main():
    n = read_ints()[0]
    for cas in xrange(n):
        s = raw_input().strip()
        print calc(s)

if __name__ == "__main__":
    main()
