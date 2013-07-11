
import sys
import os
import threading
import time


_threads_must_enumerate = False

def launch_threads(n=19):
    def run():
        while not _threads_must_enumerate:
            time.sleep(0.1)
        while True:
            threading.enumerate()

    for i in range(n):
        thr = threading.Thread(target=run)
        thr.setDaemon(True)
        thr.start()

def safe_fork():
    old = sys.getcheckinterval()
    try:
        sys.setcheckinterval(sys.maxint)
        fork_result = os.fork()
        if not fork_result:
            # Child process: reinitialize threading structures
            reload(threading)
    finally:
        sys.setcheckinterval(old)
    return fork_result

def do_fork(fork_func):
    p = fork_func()
    if not p:
        try:
            print "Child process spawned"
            report_status()
            launch_threads()
            print "Child threads launched"
            report_status()
            time.sleep(0.2)
        finally:
            os._exit(0)
    os.wait()

def report_status():
    print "in %d(%d): %d active thread(s), main thread is %s" % (
        os.getpid(), os.getppid(), threading.activeCount(), id(threading.currentThread()))

if __name__ == '__main__':
    try:
        launch_threads()

        print "\n-- With os.fork and idle threads ... \n"

        report_status()
        do_fork(os.fork)

        print "\n-- With safe_fork and enumerating threads ... \n"

        _threads_must_enumerate = True

        report_status()
        do_fork(safe_fork)

        print "\n-- With os.fork and enumerating threads ... \n"

        report_status()
        do_fork(os.fork)

        print "\n-- Shutting down!"
        sys.stdout.flush()
        time.sleep(1.0)
    finally:
        os._exit(0)

