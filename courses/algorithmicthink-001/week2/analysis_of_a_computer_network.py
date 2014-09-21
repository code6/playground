"""
Application 2 - Analysis of a computer network
"""

import random
from matplotlib import pyplot as plt
from copy import deepcopy
from p2 import compute_resilience
import time

def EXAMPLE_COMPUTER_NETWORK_graph():
    """
    Function that loads a graph given the URL
    for a text representation of the graph
    
    Returns a dictionary that models a graph
    """
    graph_text = open("alg_rf7.txt", "r").read()
    graph_lines = graph_text.split('\n')
    graph_lines = graph_lines[ : -1]
    
    answer_graph = {}
    for line in graph_lines:
        neighbors = line.split(' ')
        node = int(neighbors[0])
        answer_graph[node] = set([])
        for neighbor in neighbors[1 : -1]:
            answer_graph[node].add(int(neighbor))

    return answer_graph

def ER_graph(n, prob):
    answer_graph = {}
    for node in xrange(n):
        answer_graph[node] = set([])
    for node_x in xrange(n):
        for node_y in xrange(n):
            if node_x < node_y and random.random() <= prob:
                answer_graph[node_x].add(node_y)
                answer_graph[node_y].add(node_x)
    return answer_graph

def UPA_graph(n, m):
    class UPATrail(object):
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
                self.candi_nodes.append(self.n)
            self.n += 1
            return return_nodes

    answer_graph = {}
    for node in xrange(n):
        answer_graph[node] = set([])
    for node_x in xrange(m):
        for node_y in xrange(m):
            if node_x != node_y:
                answer_graph[node_x].add(node_y)
    dt = UPATrail(m)
    for i in xrange(n - m):
        cur = m + i
        nodes = dt.run_trail()
        for node in nodes:
            answer_graph[cur].add(node)
            answer_graph[node].add(cur)
    return answer_graph

def random_order(graph):
    """
     takes a graph and returns a list of the nodes in the graph in some random order. 
    """
    node_order = graph.keys()
    random.shuffle(node_order)
    return node_order

def targeted_order(ugraph):
    """
    Compute a targeted attack order consisting
    of nodes of maximal degree
    
    Returns:
    A list of nodes
    """
    # copy the graph
    new_graph = deepcopy(ugraph)
    
    order = []    
    while len(new_graph) > 0:
        max_degree = -1
        for node in new_graph:
            if len(new_graph[node]) > max_degree:
                max_degree = len(new_graph[node])
                max_degree_node = node
        
        neighbors = new_graph[max_degree_node]
        new_graph.pop(max_degree_node)
        for neighbor in neighbors:
            new_graph[neighbor].remove(max_degree_node)

        order.append(max_degree_node)
    return order

def fast_targeted_order(ugraph):
    """
    Compute a targeted attack order consisting
    of nodes of maximal degree
    
    Returns:
    A list of nodes
    """
    new_graph = deepcopy(ugraph)
    degree_sets = {}
    for i in xrange(len(ugraph)):
        degree_sets[i] = set()
    for node in ugraph.keys():
        degree_sets[len(ugraph[node])].add(node)

    order = []
    for degree in reversed(xrange(len(ugraph))):
        while len(degree_sets[degree]) > 0:
            node = degree_sets[degree].pop()
            order.append(node)
            for nei in new_graph[node]:
                d = len(new_graph[nei])
                degree_sets[d].remove(nei)
                degree_sets[d - 1].add(nei)
                new_graph[nei].remove(node)
    return order

def print_graph(graph):
    print "n = ", len(graph.values()), " m = ",  sum(len(l) for l in graph.values()) / 2

def q1():
    n = 1347
    g1 = EXAMPLE_COMPUTER_NETWORK_graph()
    g2 = ER_graph(n, 0.0034)
    g3 = UPA_graph(n, 2)
    c1 = compute_resilience(g1, random_order(g1))
    c2 = compute_resilience(g2, random_order(g2))
    c3 = compute_resilience(g3, random_order(g3))
    xvals = range(n + 1)
    plt.plot(xvals, c1, '-b', label='An Example computer network')
    plt.plot(xvals, c2, '-r', label='ER graph(p=%s)' % (0.0034))
    plt.plot(xvals, c3, '-g', label='UPA graph(m=%s)' % (2))
    plt.legend(loc='upper right')
    plt.xlabel('The number of nodes removed')
    plt.ylabel('The size of the largest connect component')
    plt.title('The resilience of the computer network(n=1347)')
    plt.show()

def q2():
    xvals = []
    y1vals = []
    y2vals = []
    for i in range(10, 1000, 10):
        n = i
        m = 5
        g = UPA_graph(n, m)
        t1 = time.time()
        targeted_order(g)
        t2 = time.time()
        fast_targeted_order(g)
        t3 = time.time()
        xvals.append(n)
        y1vals.append((t2 - t1) * 1000.0)
        y2vals.append((t3 - t2) * 1000.0)

    plt.plot(xvals, y1vals, '-b', label='targeted_order')
    plt.plot(xvals, y2vals, '-r', label='fast_targeted_order')
    plt.legend(loc='upper right')
    plt.xlabel('The number of nodes n')
    plt.ylabel('Running times(ms)')
    plt.title('Running time of targeted order with UPA graph by desktop Python')
    plt.show()

def q3():
    n = 1347
    g1 = EXAMPLE_COMPUTER_NETWORK_graph()
    g2 = ER_graph(n, 0.0034)
    g3 = UPA_graph(n, 2)
    c1 = compute_resilience(g1, fast_targeted_order(g1))
    c2 = compute_resilience(g2, fast_targeted_order(g2))
    c3 = compute_resilience(g3, fast_targeted_order(g3))
    xvals = range(n + 1)
    plt.plot(xvals, c1, '-b', label='An Example computer network')
    plt.plot(xvals, c2, '-r', label='ER graph(p=%s)' % (0.0034))
    plt.plot(xvals, c3, '-g', label='UPA graph(m=%s)' % (2))
    plt.legend(loc='upper right')
    plt.xlabel('The number of nodes removed')
    plt.ylabel('The size of the largest connect component')
    plt.title('The resilience of the computer network(n=1347)')
    plt.show()

if __name__ == "__main__":
    q3()
