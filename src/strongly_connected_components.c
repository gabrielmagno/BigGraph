#include <stdio.h>
#include "graph.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

void Graph_helper_StronglyConnectedComponents_strongconnect(Graph * graph, Vertex_id vertex, Vertex_id * stack, unsigned int * in_stack, unsigned int * stack_i, unsigned int * indexes, unsigned int * index, unsigned int * lowlinks, unsigned int ** strongly_connected_components, unsigned int * group_id)
{
    int i;
    Vertex_id vertex_aux;
    Vertex_id * successors;
    unsigned int n_successors;

    indexes[vertex] = ++(*index);
    lowlinks[vertex] = (*index);
    stack[(*stack_i)++] = vertex;
    in_stack[vertex] = 1;

    Graph_vertex_successors(graph, vertex, &successors, &n_successors);
    for (i = 0; i < n_successors; i++) {
        if (indexes[successors[i]] == 0) {
            Graph_helper_StronglyConnectedComponents_strongconnect(graph, successors[i], stack, in_stack, stack_i, indexes, index, lowlinks, strongly_connected_components, group_id);
            lowlinks[vertex] = MIN(lowlinks[vertex], lowlinks[successors[i]]);
        }
        else if (in_stack[successors[i]]) {
            lowlinks[vertex] = MIN(lowlinks[vertex], indexes[successors[i]]);
        }
    }
    
    if (lowlinks[vertex] == indexes[vertex]) {
        (*group_id)++;
        do {
            vertex_aux = stack[--(*stack_i)];
            in_stack[vertex_aux] = 0;
            (*strongly_connected_components)[vertex_aux] = (*group_id);
        } while(vertex_aux != vertex);
    }
}

void Graph_calculate_StronglyConnectedComponents(Graph * graph, unsigned int ** strongly_connected_components)
{
    Vertex_id vertex;
    Vertex_id * stack;
    unsigned int stack_i = 0, index = 0, group_id = 0;
    unsigned int * in_stack, * indexes, * lowlinks;
    
    stack = (Vertex_id *) malloc(((*graph).n_vertexes)*sizeof(Vertex_id));
    in_stack = (unsigned int *) malloc(((*graph).n_vertexes)*sizeof(unsigned int));
    indexes = (unsigned int *) malloc(((*graph).n_vertexes)*sizeof(unsigned int));
    lowlinks = (unsigned int *) malloc(((*graph).n_vertexes)*sizeof(unsigned int));

    for (vertex = 0; vertex < ((*graph).n_vertexes); vertex++) {
        (*strongly_connected_components)[vertex] = 0;
        in_stack[vertex] = 0;
        indexes[vertex] = 0;
    }

    for (vertex = 0; vertex < ((*graph).n_vertexes); vertex++) {
        if (indexes[vertex] == 0) {
            Graph_helper_StronglyConnectedComponents_strongconnect(graph, vertex, stack, in_stack, &stack_i, indexes, &index, lowlinks, strongly_connected_components, &group_id);
        }
    }
    
    free(stack);
    free(in_stack);
    free(indexes);
    free(lowlinks);
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

