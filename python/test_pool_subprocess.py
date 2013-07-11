import multiprocessing as mp
import os
import resource

def run_computation(x):
    resource.

def f(x):
     curr_proc=mp.current_process()
     # uncomment following line to get this to work
     curr_proc.daemon=False

     p = mp.Process(target=run_computation, args=(x,))
     p.start()
     p.join()


pool = mp.Pool(processes=4)
pool.map(f, range(10))

