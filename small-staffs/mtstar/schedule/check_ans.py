#coding=utf-8

import sys
import copy
import heapq

def read_int_line(l):
    line = l.readline()
    return [int(v) for v in line.strip().split(' ') if v]

def read_input(f):
    N,R,P,J, = read_int_line(f)
    cost = {}
    adj = {}
    radj = {}
    for i in range(N):
        k,v = read_int_line(f)
        cost[k] = v
        adj[k] = []
        radj[k] = []

    for i in range(R):
        x,y = read_int_line(f)
        adj[x].append(y)
        radj[y].append(x)

    globals().update(locals())

def read_output(f):
    user_ans, = read_int_line(f)
    pipes = []
    for i in range(P):
        pipes.append(read_int_line(f))
    globals().update(locals())

parents = {}
def search(at):
    if at in parents:
        return parents[at]
    ret = set()
    for ne in radj[at]:
        ret.add(ne)
        ret.union(search(ne))
    parents[at] = ret
    return ret

def check_user_output():
    #check each task appears excatly one time
    tasks = set()
    for p in pipes:
        for t in p:
            tasks.add(t)
    if tasks != set(cost.keys()):
        return "user tasks diff from input tasks"

    #check  ... son .. parent pattern
    for i in range(P):
        sz = len(pipes[i])
        for x in range(sz):
            for y in xrange(x + 1, sz):
                vx = pipes[i][x]
                vy = pipes[i][y]
                if vy in search(vx):
                    return "at pipe %d, %d(%d) is ahead of one of his parent %d(%d) " % (i + 1, vx, x, vy, y)

    #check simluate schedule
    deg = {}
    ready_time = {}
    is_finish = set()
    for t in tasks:
        deg[t] = len(radj[t])
        ready_time[t] = 0
    now_time = 0
    pipe_time = [0] * P
    pipe_candi = copy.deepcopy(pipes)
    finish_time = {}
    time_list = [0] * P

    def add_task(check_other_candicate = False):
        found = False

        avail = []
        for t in tasks:
            if (not t in is_finish) and deg[t] == 0 and ready_time[t] <= now_time:
                avail.append(t)

        for i in range(P):
            if pipe_time[i] > now_time: 
                continue

            if len(pipe_candi[i]) == 0:
                if check_other_candicate:
                    if len(avail) > 0:
                        return False, "at time %d, pipe %d is finished, but there are %d ready jobs left\n" % (now_time, i + 1, len(avail))
                continue

            candi = pipe_candi[i][0]

            if deg[candi] > 0 or ready_time[candi] > now_time:
                if check_other_candicate:
                    if len(avail) > 0:
                        return False, "At time %d, pipe %d 's next job %d with %d parents left, will ready at time %d. But there are %d ready jobs left\n" % (now_time, i + 1, candi, deg[candi], ready_time[candi], len(avail))
                continue

            found = True
            next_time = now_time + cost[candi]
            finish_time[candi] = next_time
            pipe_time[i] = next_time
            pipe_candi[i] = pipe_candi[i][1:]
            is_finish.add(candi)
            for ne in adj[candi]:
                deg[ne] -= 1
                ready_time[ne] = max(ready_time[ne], next_time)
            heapq.heappush(time_list, next_time)

        return found, None 

    while len(time_list) > 0:
        now_time = heapq.heappop(time_list)
        while True:
            found, err = add_task()
            if not found:
                found, err = add_task(check_other_candicate = True)
                if err:
                    return err
                break

    if finish_time[J] != user_ans:
        return "simulate ans = %d while user ans = %d\n" % (finish_time[J], user_ans)

def dump():
    #input
    print N, R, P, J
    print cost
    print adj

    #toutput
    print user_ans
    print pipes

if __name__ == "__main__":

    stand_input = 'schedule.in'
    if len(sys.argv) > 1:
        stand_input = sys.argv[1]
    user_output = 'schedule.out'
    if len(sys.argv) > 2:
        user_output = sys.argv[2]

    read_input(open(stand_input))
    read_output(open(user_output))
    ret = check_user_output()
    if ret:
        print "Error:", ret
    else:
        print "Pass answer checker!"
