#coding=utf8

import sys
import os
import time
import subprocess
import random
import config



class Client(object):
    def __init__(self, name, cmd):
        self.name = name
        self.cmd = cmd

class Server(object):
    def __init__(self):
        self.clients = {}

    def start_client(self, client):
        """ start client """
        self.clients[client.name] = subprocess.Popen(client.cmd, stdin = subprocess.PIPE, stdout = subprocess.PIPE);

    def broadcast(self, msg):
        for name, obj in self.clients.iteritems():
            obj.stdin.write(msg)

    def judge(self, who, number):
        state = "MISS"
        hit = ""
        if number == self.value:
            state = "END"
            hit = "HIT"
        else:
            if number < self.value:
                hit = "SMALL"
            else:
                hit = "BIG"
        msg = "%s GUESS %d %s\n" % (who, number, hit)
        return state, msg

    def run(self):
        self.value = random.randint(1, 1000)
        print >> sys.stderr, "target = ", self.value
        found = False
        while not found:
            print >>sys.stderr, "It's new run"
            for name, obj in self.clients.iteritems():
                obj.stdin.write("GUESS\n")
                guess_number = int(obj.stdout.readline())
                state, msg = self.judge(name, guess_number)
                self.broadcast(msg)
                print >>sys.stderr, msg,
                if state == "END":
                    msg = "END"
                    print >>sys.stderr, msg
                    self.broadcast(msg)
                    found = True
                    break

server = Server()
for c in config.client_list:
    server.start_client(Client(c["name"], c["cmd"]))
server.run()

