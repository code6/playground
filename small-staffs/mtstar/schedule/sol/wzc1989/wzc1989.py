#coding=utf-8

import sys
import copy
from collections import deque

def read_int_line(l):
    line = l.readline()
    return [int(v) for v in line.strip().split(' ') if v]

def read_input(f):
    N,R,P,J, = read_int_line(f)
    cost = {}
    tasks = []
    adj = {}
    radj = {}
    for i in range(N):
        k,v = read_int_line(f)
        tasks.append(k)
        cost[k] = v
        adj[k] = []
        radj[k] = []

    for i in range(R):
        x,y = read_int_line(f)
        adj[x].append(y)
        radj[y].append(x)

    globals().update(locals())

def get_weight(weight):
    weight[J] = 0
    que = deque()
    que.append(J)
    while len(que) > 0:
        cur = que.popleft()
        for ne in radj[cur]:
            val = weight[cur] + cost[ne]
            if ne in weight:
                val = max(val, weight[ne])
            weight[ne] = val
            que.append(ne)

def solve():
    ans = []
    for i in range(P):
        ans.append([])

    weight = {}
    get_weight(weight)

    #simluate schedule
    deg = {}
    ready_time = {}
    is_finish = set()
    for t in tasks:
        deg[t] = len(radj[t])
        ready_time[t] = 0
    now_time = 0
    pipe_time = [0] * P
    finish_time = {}
    cnt = 0

    #assert there is no job with cost = 0
    while cnt < N:
        choose_pipe = 0
        now_time = pipe_time[0]
        for i in range(P):
            if pipe_time[i] < now_time:
                now_time = pipe_time[i]
                choose_pipe = i

        best_weight = -1
        for t in tasks:
            if t in is_finish or deg[t] > 0 or ready_time[t] > now_time:
                continue
            if t in weight and weight[t] > best_weight:
                best_weight = weight[t]
                choose_task = t
            else:
                #opti need
                if best_weight == -1:
                    choose_task = t

        if choose_task == -1:
            pipe_time[choose_pipe] = min(v for v in pipe_time if v > now_time)
            continue
        
        cnt += 1
        is_finish.add(choose_task)
        pipe_time[choose_pipe] = finish_time[choose_task] = now_time + cost[choose_task]
        ans[choose_pipe].append(choose_task)
        for ne in adj[choose_task]:
            deg[ne] -= 1
            ready_time[ne] = max(ready_time[ne], finish_time[choose_task])
    # output
    print finish_time[J]
    for i in ans:
        print " ".join(str(v) for v in i)

if __name__ == "__main__":
    read_input(sys.stdin)
    solve()
