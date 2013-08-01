#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>

typedef unsigned int Vertex_id;

typedef struct Vertex {
    unsigned int out_edges_pos;
    unsigned int out_degree;
    unsigned int in_edges_pos;
    unsigned int in_degree;
} Vertex;

typedef struct Graph {
    unsigned int n_vertexes;
    unsigned int n_edges;
    Vertex * vertexes;
    Vertex_id * out_edges;
    Vertex_id * in_edges;
} Graph;

void Graph_open(Graph * graph, char * graph_filename); 

void Graph_close(Graph * graph);

void Graph_vertex_successors(Graph * graph, Vertex_id vertex, Vertex_id ** successors, unsigned int * n_successors);

void Graph_vertex_predecessors(Graph * graph, Vertex_id vertex, Vertex_id ** predecessors, unsigned int * n_predecessors);

void Graph_vertex_friends(Graph * graph, Vertex_id vertex, Vertex_id ** friends, unsigned int * n_friends);

int Graph_edge_exists(Graph * graph, Vertex_id v_from, Vertex_id v_to);

void Graph_print(Graph * graph, char * output_filename);

void Graph_print_matrix(Graph * graph, char * output_filename);

void Graph_print_friends(Graph * graph, char * output_filename);

#endif
