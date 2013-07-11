#coding=utf8

import subprocess
import time
import hashlib
import random
import json
import os

COMPILE_CMD = "g++ %s -o %s"
RUN_CMD = 'java -jar SnowCleaningVis.jar -exec "./%s %s"  -novis -seed %s 1>%s 2>&1 '

def gen_id(s):
    sedtext = hashlib.md5(s).hexdigest()[-16:].upper()
    return sedtext

def gen_fid(filename):
    filecontent = open(filename).read()
    fid = gen_id(filecontent)
    return fid

def gen_compilename(filename):
    fid = gen_fid(filename)
    compilename = filename.split('.')[0] + fid
    return compilename

def run(cmd):
    p = subprocess.Popen(cmd, shell=True)
    p.wait()

def run_compile(filename, compilename = None):
    if not compilename:
        compilename = gen_compilename(filename)
    run(COMPILE_CMD % (filename, compilename))

def run_snow(compilename, cell_size, seed, output, result_file):
    cmd = RUN_CMD % (compilename, cell_size, seed, output)
    base = time.time()
    run(cmd)
    d = {}
    d['cell_size'] = cell_size
    d['seed'] = seed
    d.update(parse_output(output))
    elipse = time.time() - base
    d['time'] = elipse
    s = json.dumps(d)
    open(result_file, "w").write(s)

def parse_output(output):
    d = {}
    for l in open(output).read().split("\n"):
        if not l.strip():
            continue
        k, v = l.strip().split('=')
        k = k.strip()
        v = v.strip()
        d[k] = v
    return d

def cp(f1, f2):
    run_compile(f1)
    run_compile(f2)
    t = random.randint(5, 10)
    print "compete %s vs %s in %d times" % (f1, f2, t)
    ans = 0
    for i in range(t):
        seed = random.randint(1, 100)
        r = []
        cell_size = random.randint(4, 15)
        for f in [f1, f2]:
            fid = gen_fid(f)
            compilename = gen_compilename(f)
            Score = 1000000000
            #for cell_size in range(3, 10):
            output = get_output_file(f, fid, seed, cell_size)
            result_file = output + ".json"
            if not os.path.exists(result_file):
                print "run snow ", compilename, cell_size, seed
                run_snow(compilename, cell_size, seed, output, result_file)
            d = json.loads(open(result_file).read())
            if Score > int(d['Score']):
                Score = int(d['Score'])
            r.append(Score)
        print r
        if r[0] == r[1]:
            continue
        if r[0] < r[1]:
            ans += 1
        else:
            ans -= 1
    print "ans = ", ans

def get_output_file(filename, fid, seed, cell_size):
    return 'output/%s_%s_%s_%s' % (filename, fid, seed, cell_size) 

def bf(filename):
    filecontent = open(filename).read()
    fid = gen_id(filecontent)
    compilename = filename.split('.')[0] + fid
    run_compile(filename, compilename)
    train_file = filename + ".train"

    for seed in range(1, 100):
        Score = 1000000000
        best_cell_size = -1
        best_d = {}
        for cell_size in range(3, 16):
            output = get_output_file(filename, fid, seed, cell_size)
            result_file = output + ".json"
            if not os.path.exists(result_file):
                print "run snow ", cell_size, seed
                run_snow(compilename, cell_size, seed, output, result_file)
            d = json.loads(open(result_file).read())
            if Score > int(d['Score']):
                Score = int(d['Score'])
                best_cell_size = cell_size
                best_d = d
        #print "seed = %s, boradsize = %s, best_cell_size = %s, Salary = %s, Fine = %s per_salary / per_fine = %lf \n" % (seed, best_d['boardsize'], best_cell_size, best_d['Salary'], best_d['Fine'], float(best_d['per_salary']) / float(best_d['per_fine']))
        print "%s,%s,%s" % (best_d['boardsize'], float(best_d['per_salary']) / float(best_d['per_fine']), best_cell_size)

cp('SnowCleaning_final.cpp', 'SnowCleaning_1.cpp')
#bf('SnowCleaning.cpp')
