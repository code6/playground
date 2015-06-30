from collections import Counter
from itertools import cycle, product as prod, permutations as perm, combinations as comb, combinations_with_replacement as combr
from sys import stdin, stdout
from collections import deque
from copy import deepcopy
MAX_REC = 26000
import sys
sys.setrecursionlimit(MAX_REC)
read_ints = lambda: map(int, raw_input().split())
read_floats = lambda: map(float, raw_input().split())


class Game(object):

    def __init__(self, peg_value, board):
        self.dir = [(-2, 0), (2, 0), (0, -2), (0, 2)]
        self.adj_dir = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        self.dir_name = ["U", "D", "L", "R"]
        self.peg_value = peg_value[:]
        self.N = len(board)
        self.bo = deepcopy(board)
        self.score = 0
        self.steps = []

    def valid_cell(self, r, c):
        return r >= 0 and r < self.N and c >= 0 and c < self.N

    def update(self, steps):
        for step in steps:
            self.run(step)

    def _run(self, r, c, dirs):
        assert self.valid_cell(r, c) and self.bo[r][c] > 0

        score = 0
        for d in dirs:
            pos = self.dir_name.index(d)
            dr, dc = self.dir[pos]
            ar, ac = self.adj_dir[pos]
            # add new peg being jumped over
            nr, nc = r + ar, c + ac
            assert self.valid_cell(nr, nc) and self.bo[nr][nc] > 0
            score += self.peg_value[self.bo[nr][nc]]
            self.bo[nr][nc] = 0
            # move jumping peg
            nr, nc = r + dr, c + dc
            assert self.valid_cell(nr, nc) and self.bo[nr][nc] == 0
            self.bo[nr][nc] = self.bo[r][c]
            self.bo[r][c] = 0
            r, c = nr, nc
        score *= len(dirs)
        self.score += score

    def run(self, step):
        r, c, dirs = step.split(' ')
        r = int(r)
        c = int(c)
        self._run(r, c, dirs)
        self.steps.append(step)

    def bf_one_step_at(self, r, c):
        assert self.valid_cell(r, c) and self.bo[r][c] > 0
        dirs = []
        other = Game(self.peg_value, self.bo)
        cr, cc = r, c
        while True:
            found = False
            cur_dirs = other.can_move(cr, cc)
            if cur_dirs:
                found = True
                d = cur_dirs[0]
                pos = self.dir_name.index(d)
                dr, dc = self.dir[pos]
                other._run(cr, cc, d)
                cr += dr
                cc += dc
                dirs.append(d)
            if not found:
                break
        if dirs:
            return "%s %s %s" % (r, c, "".join(dirs))

    def can_move(self, r, c):
        dirs = []
        if not self.valid_cell(r, c) or self.bo[r][c] == 0:
            return dirs
        for i in xrange(len(self.dir)):
            dr, dc = self.dir[i]
            ar, ac = self.adj_dir[i]
            if self.valid_cell(r + dr, c + dc) and  \
                self.bo[r + dr][c + dc] == 0 and \
                self.valid_cell(r + ar, c + ac) and \
                self.bo[r + ar][c + ac] > 0:
                dirs.append(self.dir_name[i])
        return "".join(dirs)

    def bf_one_step(self):
        for r in xrange(self.N):
            for c in xrange(self.N):
                if self.bo[r][c] > 0 and self.can_move(r, c):
                    step = self.bf_one_step_at(r, c)
                    if step:
                        self.run(step)
                        return True
        return False

    def bf(self):
        while self.bf_one_step():
            pass


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
