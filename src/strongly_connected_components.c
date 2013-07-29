#include <stdio.h>
#include "graph.h"

#define LABEL_UNKNOWN 0
#define LABEL_DISCOVERED 1
#define LABEL_EXPLORED 2


void Graph_calculate_StronglyConnectedComponents(Graph * graph, unsigned int ** strongly_connected_components)
{
    int i;
    Vertex_id vertex, actual_vertex;
    Vertex_id * adjacents, * stack_global, * stack_DFS;
    unsigned int n_adjacents, stack_global_i = 0, stack_DFS_i, group_id = 0;
    unsigned int * stack_global_in;
    char * labels_DFS;
    
    stack_global = (Vertex_id *) malloc((100*(*graph).n_vertexes)*sizeof(Vertex_id));
    stack_global_in = (unsigned int *) malloc(((*graph).n_vertexes)*sizeof(unsigned int));
    stack_DFS = (Vertex_id *) malloc(((*graph).n_vertexes)*sizeof(Vertex_id));
    labels_DFS = (char *) malloc(((*graph).n_vertexes)*sizeof(char));
    
    for (vertex = 0; vertex < ((*graph).n_vertexes); vertex++) {
        (*strongly_connected_components)[vertex] = 0;
        stack_global_in[vertex] = 0;
        labels_DFS[vertex] = LABEL_UNKNOWN;
    }
    
    for (vertex = 0; vertex < ((*graph).n_vertexes); vertex++) {
        if (!stack_global_in[vertex]) {
            labels_DFS[vertex] = LABEL_DISCOVERED;
            stack_DFS_i = 0;
            stack_DFS[stack_DFS_i++] = vertex;
            while (stack_DFS_i > 0) {
                actual_vertex = stack_DFS[--stack_DFS_i];
                Graph_vertex_successors(graph, actual_vertex, &adjacents, &n_adjacents);
                for (i = 0; i < n_adjacents; i++) {
                    if (labels_DFS[adjacents[i]] == LABEL_UNKNOWN) {
                        labels_DFS[adjacents[i]] = LABEL_DISCOVERED;
                        stack_DFS[stack_DFS_i++] = adjacents[i];
                        break;
                    }
                }
                labels_DFS[actual_vertex] = LABEL_EXPLORED;
                stack_global[stack_global_i++] = actual_vertex;
                stack_global_in[actual_vertex] = 1;
            }
        }
    }

    for (vertex = 0; vertex < ((*graph).n_vertexes); vertex++) {
        labels_DFS[vertex] = LABEL_UNKNOWN;
    }

    while (stack_global_i > 0) {
        vertex = stack_global[--stack_global_i];
        if (stack_global_in[vertex]) {
            group_id++;
            labels_DFS[vertex] = LABEL_DISCOVERED;
            stack_DFS_i = 0;
            stack_DFS[stack_DFS_i++] = vertex;
            while (stack_DFS_i > 0) {
                actual_vertex = stack_DFS[--stack_DFS_i];
                Graph_vertex_predecessors(graph, actual_vertex, &adjacents, &n_adjacents);
                for (i = 0; i < n_adjacents; i++) {
                    if (labels_DFS[adjacents[i]] == LABEL_UNKNOWN) {
                        labels_DFS[adjacents[i]] = LABEL_DISCOVERED;
                        stack_DFS[stack_DFS_i++] = adjacents[i];
                        break;
                    }
                }
                labels_DFS[actual_vertex] = LABEL_EXPLORED;
                (*strongly_connected_components)[actual_vertex] = group_id;
                stack_global_in[actual_vertex] = 0;
            }
        }
    }

    free(stack_global);
    free(stack_global_in);
    free(stack_DFS);
    free(labels_DFS);
}

int main(int argc, char * argv[])
{
    unsigned int * strongly_connected_components;
    Graph graph;
    Vertex_id vertex;

    Graph_open(&graph, NULL);
    strongly_connected_components = (unsigned int *) malloc(graph.n_vertexes*sizeof(unsigned int));

    Graph_calculate_StronglyConnectedComponents(&graph, &strongly_connected_components);

    for (vertex = 0; vertex < graph.n_vertexes; vertex++) {
        fprintf(stdout, "%d %d\n", vertex, strongly_connected_components[vertex]);
    }
    
    Graph_close(&graph);
    free(strongly_connected_components);

    return EXIT_SUCCESS;
}

