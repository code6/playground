"""
Provided code for Application portion of Module 1

Imports physics citation graph 
"""

# general imports
from matplotlib import pyplot
import random
from p1 import in_degree_distribution

###################################
# Code for loading citation graph

def load_graph(graph_filename):
    """
    Function that loads a graph given the URL
    for a text representation of the graph
    
    Returns a dictionary that models a graph
    """
    graph_text = open(graph_filename, "r").read()
    graph_lines = graph_text.split('\n')
    graph_lines = graph_lines[ : -1]
    
    print "Loaded graph with", len(graph_lines), "nodes"
    
    out_degree = []
    answer_graph = {}
    for line in graph_lines:
        neighbors = line.split(' ')
        node = int(neighbors[0])
        answer_graph[node] = set([])
        for neighbor in neighbors[1 : -1]:
            answer_graph[node].add(int(neighbor))
        out_degree.append(len(neighbors) - 1)
    print "n = ", len(graph_lines), " m = ", 1.0 * sum(out_degree) / len(out_degree)

    return answer_graph

def ER_graph(n, prob):
    answer_graph = {}
    for node in xrange(n):
        answer_graph[node] = set([])
    for node_x in xrange(n):
        for node_y in xrange(n):
            if node_x != node_y and random.random() <= prob:
                answer_graph[node_x].add(node_y)
    return answer_graph

def DPA_graph(n, m):
    class DPATrail(object):
        def __init__(self, num_nodes):
            self.n = num_nodes
            self.m = num_nodes
            self.candi_nodes = []
            for node_x in xrange(num_nodes):
                for _ in xrange(num_nodes):
                    self.candi_nodes.append(node_x)

        def run_trail(self):
            return_nodes = set()
            for _ in xrange(self.m):
                return_nodes.add(self.candi_nodes[random.randint(0, len(self.candi_nodes) - 1)])
            self.candi_nodes.append(self.n)
            for node in return_nodes:
                self.candi_nodes.append(node)
            self.n += 1
            return return_nodes

    answer_graph = {}
    for node in xrange(n):
        answer_graph[node] = set([])
    for node_x in xrange(m):
        for node_y in xrange(m):
            if node_x != node_y:
                answer_graph[node_x].add(node_y)
    dt = DPATrail(m)
    for i in xrange(n - m):
        cur = m + i
        nodes = dt.run_trail()
        for node in nodes:
            answer_graph[cur].add(node)
    return answer_graph

def plot(dic):
    items = dic.items()
    items.sort()
    x = [item[0] for item in items]
    y = [item[1] for item in items]
    pyplot.loglog(x, y, 'ro', color='blue')
    pyplot.show()

def p1():
    plot(in_degree_distribution(load_graph("alg_phys-cite.txt"), normalized=True))

def p2():
    plot(in_degree_distribution(ER_graph(2000, 0.8), normalized=True))

def p3():
    plot(in_degree_distribution(DPA_graph(27770, 14), normalized=True))

if __name__ == "__main__":
    p3()
