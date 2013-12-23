#coding=utf8

import random
import json
import sys
import re, collections

def words(text): return re.findall('[a-z]+', text.lower()) 

train_file = "training.json"
sample_input_file = "sample-test.in.json"
sample_output_file = "sample-test.out.json"

def _input(f):
    ret = []
    n = int(f.readline().strip())
    for l in f.readlines():
        l = l.strip()
        ret.append(json.loads(l))
    return ret

def input(name):
    f = open(name)
    return _input(f)

def divide(data, use_all=False):
    ret = [[], []]
    for pos, d in enumerate(data):
        ret[0 if pos % 10 != 0 or use_all else 1].append(d)
    return ret[0], ret[1]

def summary(data):
    ret = {}
    for d in data:
        category = d['category']
        section = d['section']
        ret.setdefault(section, set())
        ret[section].add(category)
    print ret
        

def build_model(data):
    model = {}
    for d in data:
        city = d['city']
        category = d['category']
        section = d['section']
        if not category in model:
            model[category] = collections.defaultdict(int)
        model[category]["HITS"] += 1
        word_list = words(d['heading']) + [section, city]
        for w in word_list:
            model[category][w] += 1
            model[category]["TOTAL_WORDS"] += 1
    summary = {}
    for d in data:
        category = d['category']
        section = d['section']
        summary.setdefault(section, set())
        summary[section].add(category)
    return model, summary

def predict(data, model, section_map):
    TOTAL_HITS = sum(model[c]["HITS"] for c in model.keys())
    result = []
    for d in data:
        nd = d.copy()
        section = nd['section']
        city = nd['city']
        candicates = []
        #for category in model.keys():
        for category in section_map[section]:
            val = 1.0 * model[category]["HITS"] / TOTAL_HITS
            val *= 1.0 * max(model[category][section], 1.0) / model[category]["TOTAL_WORDS"]
            val *= 1.0 * max(model[category][city], 1.0) / model[category]["TOTAL_WORDS"]
            for w in words(nd['heading']):
                val *= 1.0 * max(model[category][w], 1.0) / model[category]["TOTAL_WORDS"]
            candicates.append([category, val])
        #print candicates
        nd['category'] = max(candicates, key=lambda w: w[1])[0]
        result.append(nd)
    return result

def verify(predit_data, real_data):
    total = len(predit_data)
    correct = 0
    for i in xrange(total):
        correct += predit_data[i]['category'] == real_data[i]['category']
        if predit_data[i]['category'] != real_data[i]['category']:
            real_data[i]['category_predict'] = predit_data[i]['category']
            print real_data[i]
    print "correct = ", correct, " total = ", total, " ratio = ", 1.0 * correct / max(total, 1)

def output(data):
    for d in data:
        print d['category']

def training():
    input_data = input(train_file)
    train_data, test_data = divide(input_data, use_all=True)
    #summary(input_data)
    model, section_map = build_model(train_data)
    #test_result = predict(test_data, model, section_map)
    input_data = _input(sys.stdin)
    #input_data = input(sample_input_file)
    test_result = predict(input_data, model, section_map)
    output(test_result)

if __name__ == "__main__":
    training()
