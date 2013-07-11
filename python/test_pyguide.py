#coding=utf8

def get_adder(summand1):
    """Returns a function that adds numbers to a given number."""
    def adder(summand2):
        summand1 = 2
        return summand1 + summand2
    return adder

v = get_adder(1)
print v(2)
