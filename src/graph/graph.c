#include "graph.h"

void Graph_open(Graph * graph, char * graph_filename) 
{
    Vertex_id vertex, friend;
    unsigned int it, i;
    
    FILE * infile;
    if (graph_filename != NULL) {
        infile = fopen(graph_filename, "r");
    }
    else {
        infile = stdin;
    }

    // Read size of graph and allocate memory
    fscanf(infile, "%d", &((*graph).n_vertexes));
    fscanf(infile, "%d", &((*graph).n_edges));
    (*graph).vertexes = (Vertex *) malloc(((*graph).n_vertexes)*sizeof(Vertex));
    (*graph).out_edges = (Vertex_id *) malloc(((*graph).n_edges)*sizeof(Vertex_id));
    (*graph).in_edges = (Vertex_id *) malloc(((*graph).n_edges)*sizeof(Vertex_id));
    for (vertex = 0; vertex < ((*graph).n_vertexes); vertex++) {
        (*graph).vertexes[vertex] = (Vertex) {0, 0, 0, 0};
    }

    // Read the outgoing edges list
    it = 0;
    while (fscanf(infile, "%d", &vertex) == 1) {
        fscanf(infile, "%d", &((*graph).vertexes[vertex].out_degree));
        (*graph).vertexes[vertex].out_edges_pos = it;
        for (i = 0; i < ((*graph).vertexes[vertex].out_degree); i++) {
            fscanf(infile, "%d", &((*graph).out_edges[it++]));
            (*graph).vertexes[(*graph).out_edges[it-1]].in_degree++;
        }
    }
    fclose(infile);

    // Create the incoming edges list
    it = 0;
    for (vertex = 0; vertex < ((*graph).n_vertexes); vertex++) {
        (*graph).vertexes[vertex].in_edges_pos = it;
        it += (*graph).vertexes[vertex].in_degree;
    }
    for (vertex = 0; vertex < ((*graph).n_vertexes); vertex++) {
        for (i = 0; i < ((*graph).vertexes[vertex].out_degree); i++) {
            friend = (*graph).out_edges[(*graph).vertexes[vertex].out_edges_pos + i];
            (*graph).in_edges[((*graph).vertexes[friend].in_edges_pos)++] = vertex;
        }
    }
    for (vertex = 0; vertex < ((*graph).n_vertexes); vertex++) {
        (*graph).vertexes[vertex].in_edges_pos -= (*graph).vertexes[vertex].in_degree;
    }
}

void Graph_close(Graph * graph)
{
    free((*graph).vertexes);
    free((*graph).out_edges);
    free((*graph).in_edges);
}

void Graph_vertex_successors(Graph * graph, Vertex_id vertex, Vertex_id ** successors, unsigned int * n_successors)
{
    *successors = &((*graph).out_edges[(*graph).vertexes[vertex].out_edges_pos]);
    *n_successors = (*graph).vertexes[vertex].out_degree;
}

void Graph_vertex_predecessors(Graph * graph, Vertex_id vertex, Vertex_id ** predecessors, unsigned int * n_predecessors)
{
    *predecessors = &((*graph).in_edges[(*graph).vertexes[vertex].in_edges_pos]);
    *n_predecessors = (*graph).vertexes[vertex].in_degree;
}

void Graph_vertex_friends(Graph * graph, Vertex_id vertex, Vertex_id ** friends, unsigned int * n_friends)
{
    Vertex_id * out_list, * in_list;
    unsigned int out_i = 0, in_i = 0, out_degree, in_degree;
    Graph_vertex_successors(graph, vertex, &out_list, &out_degree);
    Graph_vertex_predecessors(graph, vertex, &in_list, &in_degree);
    *n_friends = 0;
    while ((out_i < out_degree) && (in_i < in_degree)) {
        if (out_list[out_i] < in_list[in_i]) {
            out_i++;
        }
        else if (out_list[out_i] > in_list[in_i]) {
            in_i++;
        }
        else {
            (*friends)[(*n_friends)++] = out_list[out_i];
            out_i++;
            in_i++;
        }
    }
}

int Graph_edge_exists(Graph * graph, Vertex_id v_from, Vertex_id v_to)
{
    Vertex_id key;
    Vertex_id * array;
    unsigned int i_min, i_mid, i_max, i, max;
    
    // Choose the smallest neighbour list to search for the edge
    if ((*graph).vertexes[v_from].out_degree < (*graph).vertexes[v_to].in_degree) {
        array = &((*graph).out_edges[(*graph).vertexes[v_from].out_edges_pos]);
        key = v_to;
        i_max = (*graph).vertexes[v_from].out_degree - 1;
    }
    else {
        array = &((*graph).in_edges[(*graph).vertexes[v_to].in_edges_pos]);
        key = v_from;
        i_max = (*graph).vertexes[v_to].in_degree - 1;
    }

    // Binary search
    i_min = 0;
    max = i_max;
    while (i_min < i_max) {
        i_mid = (i_min + i_max) >> 1;
        for (i = 0; i <= max; i++) {
        }
        if (array[i_mid] < key) {
            i_min = i_mid + 1;
        }
        else {
            i_max = i_mid;
        }
    }
    if ((i_min == i_max) && (array[i_min] == key)) {
        return 1;
    }
    else {
        return 0;
    }
}

void Graph_print(Graph * graph, char * output_filename)
{
    Vertex_id vertex;
    unsigned int edge;
    FILE * outfile;
    if (output_filename != NULL) {
        outfile = fopen(output_filename, "r");
    }
    else {
        outfile = stdout;
    }
    fprintf(outfile, "========== Adjacency List ==========\n");
    fprintf(outfile, "* G(V, E)\n* |V| = %d\n* |E| = %d\n", (*graph).n_vertexes, (*graph).n_edges);
    for (vertex = 0; vertex < ((*graph).n_vertexes); vertex++) {
        fprintf(outfile, "    + V[%d]:\n", vertex);
        fprintf(outfile, "        - Out (%d):", (*graph).vertexes[vertex].out_degree);
        for (edge = 0; edge < ((*graph).vertexes[vertex].out_degree); edge++) {
            fprintf(outfile, " %d", (*graph).out_edges[(*graph).vertexes[vertex].out_edges_pos + edge]);
        }
        fprintf(outfile, "\n");
        fprintf(outfile, "        -  In (%d):", (*graph).vertexes[vertex].in_degree);
        for (edge = 0; edge < ((*graph).vertexes[vertex].in_degree); edge++) {
            fprintf(outfile, " %d", (*graph).in_edges[(*graph).vertexes[vertex].in_edges_pos + edge]);
        }
        fprintf(outfile, "\n");
    }
    fprintf(outfile, "------------------------------------\n");
    if (output_filename != NULL) {
        fclose(outfile);
    }
}

void Graph_print_matrix(Graph * graph, char * output_filename)
{
    Vertex_id vertex_from, vertex_to;
    FILE * outfile;
    if (output_filename != NULL) {
        outfile = fopen(output_filename, "r");
    }
    else {
        outfile = stdout;
    }
    fprintf(outfile, "========== Adjacency Matrix ==========\n");
    for (vertex_from = 0; vertex_from < ((*graph).n_vertexes); vertex_from++) {
        fprintf(outfile, "%d:", vertex_from);
        for (vertex_to = 0; vertex_to < ((*graph).n_vertexes); vertex_to++) {
            fprintf(outfile, " %d", Graph_edge_exists(&(*graph), vertex_from, vertex_to));
        }
        fprintf(outfile, "\n");
    }
    fprintf(outfile, "--------------------------------------\n");
    if (output_filename != NULL) {
        fclose(outfile);
    }
}

void Graph_print_friends(Graph * graph, char * output_filename)
{
    Vertex_id vertex;
    Vertex_id * friends;
    unsigned int i, n_friends;
    FILE * outfile;
    if (output_filename != NULL) {
        outfile = fopen(output_filename, "r");
    }
    else {
        outfile = stdout;
    }
    fprintf(outfile, "========== Friends List ==========\n");
    friends = (Vertex_id *) malloc((*graph).n_vertexes*sizeof(Vertex_id));
    for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {
        Graph_vertex_friends(graph, vertex, &friends, &n_friends);
        fprintf(outfile, "%d:", vertex);
        for (i = 0; i < n_friends; i++) {
            fprintf(outfile, " %d", friends[i]);
        }
        fprintf(outfile, "\n");
    }
    free(friends);
    fprintf(outfile, "----------------------------------\n");
    if (output_filename != NULL) {
        fclose(outfile);
    }
}
