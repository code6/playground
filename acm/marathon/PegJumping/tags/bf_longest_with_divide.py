from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
from collections import deque
from Queue import Queue
from copy import deepcopy
MAX_REC = 26000
import sys
import heapq
sys.setrecursionlimit(MAX_REC)
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())

MAX_STATE = 1000
DIR = [(-2, 0), (2, 0), (0, -2), (0, 2)]
ADJ_DIR = [(-1, 0), (1, 0), (0, -1), (0, 1)]
DIR_NAME = ["U", "D", "L", "R"]


def cerr(msg):
    print >> sys.stderr, msg
    sys.stderr.flush()


class State(object):

    def __init__(self, game, r, c):
        self.game = game
        self.r = r
        self.c = c
        self.cr = r
        self.cc = c
        self.sum = 0
        self.dirs = []
        self.used_peg_set = set()

    def can_move(self, d):
        pos = DIR_NAME.index(d)
        dr, dc = DIR[pos]
        br, bc = ADJ_DIR[pos]
        cr, cc = self.cr + dr, self.cc + dc
        ar, ac = self.cr + br, self.cc + bc
        if self.game.valid_cell(cr, cc) and (
            not self.game.has_peg(cr, cc) or (cr == self.r and cc == self.c)
        ) and self.game.valid_cell(ar, ac) and (self.game.has_peg(ar, ac)) and (
            not (ar, ac) in self.used_peg_set):
            return True

    def run(self, d):
        pos = DIR_NAME.index(d)
        dr, dc = DIR[pos]
        br, bc = ADJ_DIR[pos]
        cr, cc = self.cr + dr, self.cc + dc
        ar, ac = self.cr + br, self.cc + bc
        self.sum += self.game.value(ar, ac)
        self.dirs.append(d)
        self.used_peg_set.add((ar, ac))
        self.cr = cr
        self.cc = cc

    def copy(self):
        state = State(self.game, self.r, self.c)
        state.cr = self.cr
        state.cc = self.cc
        state.sum = self.sum
        state.dirs = self.dirs[:]
        state.used_peg_set = deepcopy(self.used_peg_set)
        return state

    def score(self):
        return self.sum * len(self.dirs)

    def __str__(self):
        return "(r=%s, c = %s, cr=%s, cc=%s, score = %s, dirs=%s)" % (
            self.r, self.c, self.cr, self.cc, self.score(), "".join(self.dirs)
        )

    def step(self):
        return "%s %s %s" % (self.r, self.c, "".join(self.dirs))


class Game(object):

    def __init__(self, peg_value, board):
        self.peg_value = peg_value[:]
        self.N = len(board)
        self.bo = deepcopy(board)
        self.score = 0
        self.steps = []

    def valid_cell(self, r, c):
        return r >= 0 and r < self.N and c >= 0 and c < self.N

    def has_peg(self, r, c):
        return self.valid_cell(r, c) and self.bo[r][c] > 0

    def value(self, r, c):
        return self.peg_value[self.bo[r][c]]

    def update(self, steps):
        for step in steps:
            self.run(step)

    def merge(self, groups):
        ret = set()
        for g in groups:
            ret = ret.union(g)
        return ret

    def divide(self, peg_list):
        groups = []
        vis = set()
        for x,y in peg_list:
            if not (self.has_peg(x, y) and not (x, y) in vis):
                continue
            g = set()
            g.add((x, y))
            vis.add((x, y))
            Q = Queue()
            Q.put((x, y))
            while not Q.empty():
                r, c = Q.get()
                for dr in [-2, -1, 0, 1, 2]:
                    for dc in [-2, -1, 0, 1, 2]:
                        nr, nc = r + dr, c + dc
                        if not (self.has_peg(nr, nc) and not (nr, nc) in
                                vis):
                            continue
                        g.add((nr, nc))
                        Q.put((nr, nc))
                        vis.add((nr,nc))
            groups.append(g)
        return groups

    def run(self, step):
        r, c, dirs = step.split(' ')
        r = int(r)
        c = int(c)
        assert self.valid_cell(r, c) and self.has_peg(r, c)

        sum = 0
        for d in dirs:
            pos = DIR_NAME.index(d)
            dr, dc = DIR[pos]
            ar, ac = ADJ_DIR[pos]
            # add new peg being jumped over
            nr, nc = r + ar, c + ac
            assert self.valid_cell(nr, nc) and self.bo[nr][nc] > 0
            sum += self.peg_value[self.bo[nr][nc]]
            self.bo[nr][nc] = 0
            # move jumping peg
            nr, nc = r + dr, c + dc
            assert self.valid_cell(nr, nc) and self.bo[nr][nc] == 0
            self.bo[nr][nc] = self.bo[r][c]
            self.bo[r][c] = 0
            r, c = nr, nc
        self.score += sum * len(dirs)
        self.steps.append(step)
        return r, c

    def h(self):
        pass

    def bf_one_largest_step_at(self, r, c):
        assert self.valid_cell(r, c) and self.has_peg(r, c)
        best = state = State(self, r, c)
        cur_list = [state]
        dep = 0
        while len(cur_list) > 0:
            dep += 1
            cur_list = sorted(cur_list, key=lambda s: -s.score())
            next_list = []
            for i in xrange(min(len(cur_list), MAX_STATE)):
                state = cur_list[i]
                for d in DIR_NAME:
                    if state.can_move(d):
                        new_state = state.copy()
                        new_state.run(d)
                        if best.score() < new_state.score():
                            best = new_state
                        next_list.append(new_state)
            cur_list = next_list
        return best

    def can_move(self, r, c):
        dirs = []
        if not self.valid_cell(r, c) or self.bo[r][c] == 0:
            return dirs
        for i in xrange(len(DIR)):
            dr, dc = DIR[i]
            ar, ac = ADJ_DIR[i]
            if self.valid_cell(r + dr, c + dc) and  \
                not self.has_peg(r + dr, c + dc) and \
                self.valid_cell(r + ar, c + ac) and \
                self.has_peg(r + ar, c + ac):
                dirs.append(DIR_NAME[i])
        return "".join(dirs)

    def bf_one_step(self, group):
        best = None
        for r, c in group:
            if self.has_peg(r, c) and self.can_move(r, c):
                #cerr("at bf_one_step, r=%s, c=%s" % (r, c))
                state = self.bf_one_largest_step_at(r, c)
                if not best or best < state:
                    best = state

        if best:
            return best.step()

    def bf(self):
        peg_list = [(i, j) for i in xrange(self.N) for j in xrange(self.N) if self.has_peg(i, j)]
        groups = self.divide(peg_list)
        while groups:
            cerr("group.size = %s" % len(groups))
            g = groups.pop()
            step = self.bf_one_step(g)
            if step:
                r, c = self.run(step)
                g.add((r, c))
                for ng in self.divide(g):
                    groups.append(g)

class PegJumping(object):

    def getMoves(self, peg_value, board_):
        peg_value.insert(0, 0)
        board = []
        N = len(board_)
        for i in xrange(N):
            line = []
            for j in xrange(N):
                line.append(0 if board_[i][j] == '.' else int(board_[i][j]) + 1)
            board.append(line)
        peg = Game(peg_value, board)
        peg.bf()
        return peg.steps


def main():
    M = read_ints()[0]
    peg_value = []
    for i in xrange(M):
        peg_value.append(read_ints()[0])
    N = read_ints()[0]
    board = []
    for i in xrange(N):
        line = raw_input()
        board.append(line)
    peg = PegJumping()
    ret = peg.getMoves(peg_value, board)
    print len(ret)
    for l in ret:
        print l
    stdout.flush()


if __name__ == '__main__':
    main()
