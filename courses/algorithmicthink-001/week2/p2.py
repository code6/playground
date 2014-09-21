#coding=utf8
"""
Project 2 -  Connected components and graph resilience
"""

from collections import deque

def bfs_visited(ugraph, start_node):
    """
    breadth-first search return the set of node visited from start_node
    """
    que = deque()
    visited = set([start_node])
    que.append(start_node)
    while len(que) > 0:
        cur = que.pop()
        for nei in ugraph[cur]:
            if not nei in visited:
                visited.add(nei)
                que.append(nei)
    return visited

def cc_visited(ugraph):
    """
    compute the set of connected components (CCs) of an undirected graph
    """
    visited = set()
    ccs = []
    for start_node in ugraph.keys():
        if start_node in visited:
            continue
        cur_vis = bfs_visited(ugraph, start_node)
        visited.update(cur_vis)
        ccs.append(cur_vis)
    return ccs

def largest_cc_size(ugraph):
    """
     returns the size (an integer) of the largest connected component in ugraph.
    """
    return max([len(cc) for cc in cc_visited(ugraph)])


def union(node_info, node_x, node_y):
    """
        union for compute_resilience
    """
    node_x = find(node_info, node_x)
    node_y = find(node_info, node_y)
    if node_x == node_y:
        return 0
    node_info[node_x]["parent"] = node_y
    node_info[node_y]["size"] += node_info[node_x]["size"]
    return node_info[node_y]["size"]

def find(node_info, node_x):
    """
        find for compute_resilience
    """
    if node_info[node_x]["parent"] == node_x:
        return node_x
    node_info[node_x]["parent"] = find(node_info, node_info[node_x]["parent"])
    return node_info[node_x]["parent"] 

def compute_resilience(ugraph, attack_order):
    """
    Takes the undirected graph ugraph, a list of nodes attack_order and iterates through the nodes in attack_order. For each node in the list, the function removes the given node and its edges from the graph and then computes the size of the largest connected component for the resulting graph.
    """
    attack_set = set(attack_order)

    node_info = {}
    for node in ugraph.keys():
        if not node in attack_set:
            node_info[node] = { "parent": node, "size":1}

    max_cc = int(len(node_info) > 0)
    for node in ugraph.keys():
        if not node in attack_set:
            for nei in ugraph[node]:
                if not nei in attack_set:
                    max_cc = max(max_cc, union(node_info, node, nei))

    resilience_list = []
    resilience_list.append(max_cc)
    for node in reversed(attack_order):
        attack_set.remove(node)
        node_info[node] = { "parent": node, "size":1}
        max_cc = max(max_cc, 1)
        for nei in ugraph[node]:
            if not nei in attack_set:
                max_cc = max(max_cc, union(node_info, node, nei))
        resilience_list.append(max_cc)
    resilience_list.reverse()
    return resilience_list

if __name__ == "__main__":
    EX_GRAPH0 = {0: set([1 , 2]), 1:set([0,1]), 2:set([0,1])}
    EX_GRAPH1 = {0: set([1,4, 5]),
              1: set([2, 6]),
              2: set([3]),
              3: set([0]),
              4: set([1]),
              5: set([2]),
              6: set([]),
    }
    print bfs_visited(EX_GRAPH1, 6)
    print cc_visited(EX_GRAPH1)
    print largest_cc_size(EX_GRAPH1)
    print compute_resilience(EX_GRAPH0, [1, 2])

