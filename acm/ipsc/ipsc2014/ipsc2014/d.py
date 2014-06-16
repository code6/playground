from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
import sys

def main():
    x = 80000000
    y = 70000000
    message = "hello world"
    s = "\0" * x + message + "\0" * y
    open("d_test.in", "w").write(s)

if __name__ == "__main__":
    main()
