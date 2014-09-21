#coding=utf8
"""
Project 1 - Degree distributions for graphs
"""

EX_GRAPH0 = {0: set([1 , 2]), 1:set([]), 2:set([])}

EX_GRAPH1 = {0: set([1,4, 5]),
          1: set([2, 6]),
          2: set([3]),
          3: set([0]),
          4: set([1]),
          5: set([2]),
          6: set([]),
}

EX_GRAPH2 = {0: set([1, 4, 5]),
          1: set([2,6]),
          2: set([3,7]),
          3: set([7]),
          4: set([1]),
          5: set([2]),
          6: set([]),
          7: set([3]),
          8: set([1,2]),
          9: set([0,  4, 5, 6, 7, 3])
}


def make_complete_graph(num_nodes):
    """
    Takes the number of nodes num_nodes and returns a dictionary corresponding to a complete directed graph with the specified number of nodes. 
    """
    graph = {}
    if num_nodes <= 0:
        return graph
    for ni in xrange(num_nodes):
        graph[ni] = set()
        for nj in xrange(num_nodes):
            if ni != nj:
                graph[ni].add(nj)
    return graph

def compute_in_degrees(digraph):
    """
    Takes a directed graph digraph (represented as a dictionary) and computes the in-degrees for the nodes in the graph. 
    """
    in_degree = {}
    for node, edge_set in digraph.iteritems():
        if not node in in_degree:
            in_degree[node] = 0
        for target_node in edge_set:
            if not target_node in in_degree:
                in_degree[target_node] = 0
            in_degree[target_node] += 1
    return in_degree

def in_degree_distribution(digraph, normalized=False):
    """
    Takes a directed graph digraph (represented as a dictionary) and computes the unnormalized distribution of the in-degrees of the graph. 
    """
    in_degree = compute_in_degrees(digraph)
    distri = {}
    for ind in in_degree.values():
        if ind not in distri:
            distri[ind] = 0
        distri[ind] += 1
    if normalized:
        total_degree = 0
        for ind, cnt in distri.iteritems():
            total_degree += cnt
        for ind, cnt in distri.iteritems():
            distri[ind] = 1.0 * cnt / total_degree
            
    return distri

if __name__ == "__main__":
    print compute_in_degrees(EX_GRAPH0)
    print in_degree_distribution(EX_GRAPH0)
    print compute_in_degrees(EX_GRAPH1)
    print in_degree_distribution(EX_GRAPH1)
    print compute_in_degrees(EX_GRAPH2)
    print in_degree_distribution(EX_GRAPH2)
    print in_degree_distribution(EX_GRAPH2, normalized=True)
