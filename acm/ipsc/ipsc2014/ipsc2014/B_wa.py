#coding=utf8
MOD = 2 ** 32
c = []

def random(x, i):
    global c
    t = x[i-22] - x[i-43] - c[-1]
    z = t % MOD
    c.append(1 if t < 0 else 0)
    x.append(z)
    return z

def main():
    global c
    """
    c = [0] * 43
    x = [0] * 43
    for i in xrange(43):
        x[i] = 999999999 * (i ** 3) % MOD
    print random(x, 43)
    print random(x, 44)
    print random(x, 45)
    """

    t = input()
    for testCase in range(t):
        raw_input()

        c = [0] * 43
        randomI = 43

        n = int(raw_input())
        state = map(int, raw_input().split())

        all_zero = len([ v for v in state if v]) == 0
        if all_zero:
            print "all zero!!"
        else:
            print testCase, " is ok"


        x = map(int, raw_input().split())
        moveNum = input()
        moves = raw_input()

        continue

        for move in moves:
            if move == 'r':
                state = state[::-1]
            #print n, state

            i = 0
            j = 0
            while i < n:
                #print i, j, n
                if state[i] == 0:
                    i += 1
                    continue

                if i+1<n and state[i] == state[i+1]:
                    state[j] = state[i] << 1
                    j += 1
                    i += 2
                else:
                    state[j] = state[i]
                    i += 1
                    j += 1

            num_empty = n - 1 - j
            new_value = 2
            pos = j + 1
            flag = False
            if j + 1 < n:
                flag = True
                pos = random(x, randomI) % num_empty + j + 1
                randomI += 1

                if (random(x, randomI) % 10) == 0:
                    new_value = 4
                randomI += 1

            while j < n:
                state[j] = 0
                j += 1

            if flag:
                state[pos] = new_value

            if move == 'r':
                state = state[::-1]

        #print ' '.join(map(str, state))

if __name__ == '__main__':
    main()
