"""
Example code for creating and visualizing
cluster of county-based cancer risk data

Note that you must download the file
http://www.codeskulptor.org/#alg_clusters_matplotlib.py
to use the matplotlib version of this code
"""

# Flavor of Python - desktop or CodeSkulptor
DESKTOP = True

import math
import random
import urllib2
import alg_cluster

# conditional imports
if DESKTOP:
    import alg_project3      # desktop project solution
    import alg_clusters_matplotlib
else:
    #import userXX_XXXXXXXX as alg_project3   # CodeSkulptor project solution
    import alg_clusters_simplegui
    import codeskulptor
    codeskulptor.set_timeout(30)


###################################################
# Code to load data tables

# URLs for cancer risk data tables of various sizes
# Numbers indicate number of counties in data table

DIRECTORY = "http://commondatastorage.googleapis.com/codeskulptor-assets/"
DATA_3108_URL = DIRECTORY + "data_clustering/unifiedCancerData_3108.csv"
DATA_896_URL = DIRECTORY + "data_clustering/unifiedCancerData_896.csv"
DATA_290_URL = DIRECTORY + "data_clustering/unifiedCancerData_290.csv"
DATA_111_URL = DIRECTORY + "data_clustering/unifiedCancerData_111.csv"


def load_data_from_url(data_url):
    data_file = urllib2.urlopen(data_url)
    data = data_file.read()
    data_lines = data.split('\n')
    return load_data_table(data_lines)

def load_data_from_file(data_file):
    data_lines = open(data_file, "r").read().split('\n')
    return load_data_table(data_lines)

def load_data_table(data_lines):
    """
    Import a table of county-based cancer risk data
    from a csv format file
    """
    print "Loaded", len(data_lines), "data points"
    data_tokens = [line.split(',') for line in data_lines]
    return [[tokens[0], float(tokens[1]), float(tokens[2]), int(tokens[3]), float(tokens[4])] 
            for tokens in data_tokens]


############################################################
# Code to create sequential clustering
# Create alphabetical clusters for county data

def sequential_clustering(singleton_list, num_clusters):
    """
    Take a data table and create a list of clusters
    by partitioning the table into clusters based on its ordering
    
    Note that method may return num_clusters or num_clusters + 1 final clusters
    """
    
    cluster_list = []
    cluster_idx = 0
    total_clusters = len(singleton_list)
    cluster_size = float(total_clusters)  / num_clusters
    
    for cluster_idx in range(len(singleton_list)):
        new_cluster = singleton_list[cluster_idx]
        if math.floor(cluster_idx / cluster_size) != \
           math.floor((cluster_idx - 1) / cluster_size):
            cluster_list.append(new_cluster)
        else:
            cluster_list[-1] = cluster_list[-1].merge_clusters(new_cluster)
            
    return cluster_list

def gen_singleton_list(data_table):
    singleton_list = []
    for line in data_table:
        singleton_list.append(alg_cluster.Cluster(set([line[0]]), line[1], line[2], line[3], line[4]))
    return singleton_list
                

#####################################################################
# Code to load cancer data, compute a clustering and 
# visualize the results


def run_example():
    """
    Load a data table, compute a list of clusters and 
    plot a list of clusters

    Set DESKTOP = True/False to use either matplotlib or simplegui
    """
    #data_table = load_data_table(DATA_3108_URL)
    #data_table = load_data_from_file("unifiedCancerData_290.csv")
    #data_table = load_data_from_file("unifiedCancerData_896.csv")
    #data_table = load_data_from_file("unifiedCancerData_3108.csv")
    data_table = load_data_from_file("unifiedCancerData_111.csv")
    singleton_list = gen_singleton_list(data_table)
    

    #print alg_project3.fast_closest_pair(singleton_list)
    #print alg_project3.slow_closest_pairs(singleton_list)
        
    #cluster_list = sequential_clustering(singleton_list, 15)    
    #print "Displaying", len(cluster_list), "sequential clusters"

    cluster_list = alg_project3.kmeans_clustering(singleton_list, 9, 5)
    print "Displaying", len(cluster_list), "k-means clusters"
    print "compute_distortion : ", alg_project3.compute_distortion(cluster_list, data_table)

    cluster_list = alg_project3.hierarchical_clustering(singleton_list, 9)
    print "Displaying", len(cluster_list), "hierarchical clusters"
    print "compute_distortion : ", alg_project3.compute_distortion(cluster_list, data_table)

    #for cluster in cluster_list:
    #    print cluster

            
    #draw the clusters using matplotlib or simplegui
    #if DESKTOP:
    #    alg_clusters_matplotlib.plot_clusters(data_table, cluster_list, True)
    #else:
    #    alg_clusters_simplegui.PlotClusters(data_table, cluster_list)
    #
if __name__ == "__main__":
    run_example()





    





  
        






        





