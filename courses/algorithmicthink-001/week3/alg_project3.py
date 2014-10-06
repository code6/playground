#coding=utf8
"""
Template for Project 3
Student will implement four functions:

slow_closest_pairs(cluster_list)
fast_closest_pair(cluster_list) - implement fast_helper()
hierarchical_clustering(cluster_list, num_clusters)
kmeans_clustering(cluster_list, num_clusters, num_iterations)

where cluster_list is a list of clusters in the plane
"""

import math
import random
import time
import alg_cluster
import alg_project3_viz
from matplotlib import pyplot as plt

EPS = 1e-9


def pair_distance(cluster_list, idx1, idx2):
    """
    Helper function to compute Euclidean distance between two clusters
    in cluster_list with indices idx1 and idx2
    
    Returns tuple (dist, idx1, idx2) with idx1 < idx2 where dist is distance between
    cluster_list[idx1] and cluster_list[idx2]
    """
    return (cluster_list[idx1].distance(cluster_list[idx2]), min(idx1, idx2), max(idx1, idx2))


def slow_closest_pairs(cluster_list):
    """
    Compute the set of closest pairs of cluster in list of clusters
    using O(n^2) all pairs algorithm
    
    Returns the set of all tuples of the form (dist, idx1, idx2) 
    where the cluster_list[idx1] and cluster_list[idx2] have minimum distance dist.   
    
    """
    
    min_dist = -1.0
    min_list = []
    cluster_size = len(cluster_list)
    for idx1 in range(cluster_size):
        for idx2 in range(cluster_size):
            if idx1 == idx2:
                continue
            dist_tuple = pair_distance(cluster_list, idx1, idx2)
            dist = dist_tuple[0]
            if min_dist < 0 or dist < min_dist - EPS:
                min_dist = dist
                min_list = [dist_tuple]
            elif abs(dist - min_dist) < EPS:
                min_list.append(dist_tuple)
    return set(min_list)


def fast_closest_pair(cluster_list):
    """
    Compute a closest pair of clusters in cluster_list
    using O(n log(n)) divide and conquer algorithm
    
    Returns a tuple (distance, idx1, idx2) with idx1 < idx 2 where
    cluster_list[idx1] and cluster_list[idx2]
    have the smallest distance dist of any pair of clusters
    """
        
    def fast_helper(cluster_list, horiz_order, vert_order):
        """
        Divide and conquer method for computing distance between closest pair of points
        Running time is O(n * log(n))
        
        horiz_order and vert_order are lists of indices for clusters
        ordered horizontally and vertically
        
        Returns a tuple (distance, idx1, idx2) with idx1 < idx 2 where
        cluster_list[idx1] and cluster_list[idx2]
        have the smallest distance dist of any pair of clusters
    
        """
        num = len(horiz_order)
        
        # base case
        if num <= 1:
            return (1e30, 0, 0)
        if num <= 3:
            result =  list(slow_closest_pairs([cluster_list[pos] for pos in horiz_order]))[0]
            #mapping cluster index
            result = (result[0], horiz_order[result[1]], horiz_order[result[2]])
            return result
        
        # divide
        half = num / 2
        horiz_left_index = horiz_order[0:half]
        horiz_right_index = horiz_order[half:num]
        vert_left_index = [pos for pos in vert_order if pos in horiz_left_index]
        vert_right_index = [pos for pos in vert_order if pos in horiz_right_index]
        dist_tuple_left = fast_helper(cluster_list, horiz_left_index, vert_left_index)
        dist_tuple_right = fast_helper(cluster_list, horiz_right_index, vert_right_index)
        
        # conquer
        dist_tuple = min(dist_tuple_left, dist_tuple_right)
        horiz_mid_val = 0.5 * (cluster_list[horiz_order[half - 1]].horiz_center() + cluster_list[horiz_order[half]].horiz_center())

        check_pos_list = [ pos for pos in vert_order if abs(cluster_list[pos].horiz_center() - horiz_mid_val) < dist_tuple[0]]
        check_num = len(check_pos_list)
        for idx_u in range(check_num):
            for idx_v in range(idx_u + 1, min(idx_u + 3, check_num - 1) + 1):
                dist_tuple = min(dist_tuple, pair_distance(cluster_list, check_pos_list[idx_u], check_pos_list[idx_v]))
        #print "dist_tuple = ", dist_tuple
        return dist_tuple
            
    # compute list of indices for the clusters ordered in the horizontal direction
    hcoord_and_index = [(cluster_list[idx].horiz_center(), idx) 
                        for idx in range(len(cluster_list))]    
    hcoord_and_index.sort()
    horiz_order = [hcoord_and_index[idx][1] for idx in range(len(hcoord_and_index))]
     
    # compute list of indices for the clusters ordered in vertical direction
    vcoord_and_index = [(cluster_list[idx].vert_center(), idx) 
                        for idx in range(len(cluster_list))]    
    vcoord_and_index.sort()
    vert_order = [vcoord_and_index[idx][1] for idx in range(len(vcoord_and_index))]

    # compute answer recursively
    answer = fast_helper(cluster_list, horiz_order, vert_order) 
    return (answer[0], min(answer[1:]), max(answer[1:]))


def hierarchical_clustering(cluster_list, num_clusters):
    """
    Compute a hierarchical clustering of a set of clusters
    Note: the function mutates cluster_list
    
    Input: List of clusters, number of clusters
    Output: List of clusters whose length is num_clusters
    """
    while len(cluster_list) > num_clusters:
        #print "before loop: ", len(cluster_list), num_clusters
        #dist_tuple = list(slow_closest_pairs(cluster_list))[0]
        dist_tuple = fast_closest_pair(cluster_list)
        idx1, idx2 = dist_tuple[1:]
        cluster_list[idx1].merge_clusters(cluster_list[idx2])
        cluster_list.pop(idx2)
    return cluster_list
    
def kmeans_clustering(cluster_list, num_clusters, num_iterations):
    """
    Compute the k-means clustering of a set of clusters
    
    Input: List of clusters, number of clusters, number of iterations
    Output: List of clusters whose length is num_clusters
    """
    
    num = len(cluster_list)
    cluster_index = range(num)
    cluster_index.sort(key=lambda x:cluster_list[x].total_population())
    cluster_index.reverse()
    # initialize k-means clusters to be initial clusters with largest populations
    center_list = [ cluster_list[cluster_index[pos]].copy() for pos in range(num_clusters) ]
    prev_center_list = []

    for _ in range(num_iterations):
        prev_center_list = center_list
        center_list = []
        for idx in range(num_clusters):
            center_list.append(alg_cluster.Cluster(set(), 0.0, 0.0, 0, 0.0))
        best_idx_list = []
        for idx in range(num):
            best_dist = prev_center_list[0].distance(cluster_list[idx])
            best_idx = 0
            for cidx in range(num_clusters):
                dist = prev_center_list[cidx].distance(cluster_list[idx])
                if best_dist > dist:
                    best_idx = cidx
                    best_dist = dist
            best_idx_list.append(best_idx)
        for idx in range(num):
            center_list[best_idx_list[idx]].merge_clusters(cluster_list[idx])

    return center_list

def gen_random_clusters(num_clusters):
    """
     Creates a list of clusters where each cluster in this list corresponds to one randomly generated point in the square with corners (±1,±1)
    """
    cluster_list = []
    for _ in range(num_clusters):
        p = (random.random() * 2.0 - 1.0, random.random() * 2.0 - 1.0)
        cluster_list.append(alg_cluster.Cluster(set(p), p[0], p[1], 0, 0.0))
    return cluster_list

def compute_distortion(cluster_list, data_table):
    distortion = 0
    for cluster in cluster_list:
        distortion += cluster.cluster_error(data_table)
    return distortion

def q1():
    xvals = []
    y1vals = []
    y2vals = []
    for num_clusters in range(2, 201):
        cluster_list = gen_random_clusters(num_clusters)
        t1 = time.time()
        slow_closest_pairs(cluster_list)
        t2 = time.time()
        fast_closest_pair(cluster_list)
        t3 = time.time()
        xvals.append(num_clusters)
        y1vals.append((t2 - t1))
        y2vals.append((t3 - t2))
    plt.plot(xvals, y1vals, '-b', label='slow_closest_pairs')
    plt.plot(xvals, y2vals, '-r', label='fast_closest_pair')
    plt.legend(loc='upper right')
    plt.xlabel('The number of initial clusters')
    plt.ylabel('Running times in seconds')
    plt.title('Running time of slow_closest_pairs/fast_closest_pair by desktop Python')
    plt.show()

def q10():
    #county_size = 111
    #county_size = 290 
    county_size = 896
    xvals = range(6, 21)
    data_table = alg_project3_viz.load_data_from_file("unifiedCancerData_%d.csv" % (county_size))
    y1vals = []
    #k-means
    singleton_list = alg_project3_viz.gen_singleton_list(data_table)
    for num_clusters in xvals:
        y1vals.append(compute_distortion(kmeans_clustering(singleton_list, num_clusters, 5), data_table))

    #hierarchical
    y2vals = []
    singleton_list = alg_project3_viz.gen_singleton_list(data_table)
    for num_clusters in reversed(xvals):
        y2vals.append(compute_distortion(hierarchical_clustering(singleton_list, num_clusters), data_table))
    y2vals.reverse()

    plt.plot(xvals, y2vals, '-b', label='hierarchical_clustering')
    plt.plot(xvals, y1vals, '-r', label='kmeans_clustering')
    plt.legend(loc='upper right')
    plt.xlabel('The number of output clusters')
    plt.ylabel('The distortion of the clustering')
    plt.title('%d county data sets' % (county_size))
    plt.show()


if __name__ == "__main__":
    q10()
