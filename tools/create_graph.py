#! /usr/bin/python

import sys
import networkx

def read_graph(filename):
    graph = networkx.DiGraph()
    infile = open(filename, "r")
    n_nodes = infile.readline()
    n_edges = infile.readline()
    for line in infile:
        node_from, node_outdegree, successors_str = line.rstrip().split(" ", 2)
        successors = successors_str.split(" ")
        for node_to in successors:
            graph.add_edge(node_from, node_to)
    infile.close()
    return graph

def graph_print(graph):
    sys.stdout.write("%d\n" % (graph.order()));
    sys.stdout.write("%d\n" % (graph.size()));
    for v in graph.nodes():
        sys.stdout.write("%s %d %s\n" % (str(v), graph.out_degree(v), " ".join(map(str, sorted(graph.successors(v))))))

def graph_print_edges(graph):
    for a, b in graph.edges_iter():
        sys.stdout.write("%d %d\n" % (a, b))

if __name__ == "__main__":

    n = int(sys.argv[1])
    p = float(sys.argv[2])

    graph = networkx.fast_gnp_random_graph(n, p, directed=True)

    graph_print_edges(graph)
    #graph_print(graph)
