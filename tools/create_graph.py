#! /usr/bin/python

import sys
import networkx

def graph_print(graph):
    sys.stdout.write("%d\n" % (graph.order()));
    sys.stdout.write("%d\n" % (graph.size()));
    for v in graph.nodes():
        sys.stdout.write("%s %d %s\n" % (str(v), graph.out_degree(v), " ".join(map(str, sorted(graph.successors(v))))))

def graph_print_edges(graph):
    for a, b in graph.edges_iter():
        sys.stdout.write("%d %d\n" % (a, b))

n = int(sys.argv[1])
p = float(sys.argv[2])

graph = networkx.fast_gnp_random_graph(n, p, directed=True)

#graph_print_edges(graph)
graph_print(graph)
