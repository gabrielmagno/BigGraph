#include "strongly_connected_components.h"

void Graph_calculate_StronglyConnectedComponents(Graph * graph, unsigned int ** strongly_connected_components)
{
    Vertex_id vertex, actual_vertex;
    Vertex_id * adjacents, * stack_global, * stack_DFS;
    unsigned int i, n_adjacents, stack_global_i = 0, stack_DFS_i, group_id = 0, stack_DFS_i_aux;
    char * labels_DFS;
    
    stack_global = (Vertex_id *) malloc((100*(*graph).n_vertexes)*sizeof(Vertex_id));
    stack_DFS = (Vertex_id *) malloc(((*graph).n_vertexes)*sizeof(Vertex_id));
    labels_DFS = (char *) malloc(((*graph).n_vertexes)*sizeof(char));
    
    for (vertex = 0; vertex < ((*graph).n_vertexes); vertex++) {
        (*strongly_connected_components)[vertex] = 0;
        labels_DFS[vertex] = LABEL_UNKNOWN;
    }
    
    for (vertex = 0; vertex < ((*graph).n_vertexes); vertex++) {
        if (labels_DFS[vertex] == LABEL_UNKNOWN) {
            labels_DFS[vertex] = LABEL_DISCOVERED;
            stack_DFS_i = 0;
            stack_DFS[stack_DFS_i++] = vertex;
            while (stack_DFS_i > 0) {
                actual_vertex = stack_DFS[stack_DFS_i-1];
                stack_DFS_i_aux = stack_DFS_i;
                Graph_vertex_successors(graph, actual_vertex, &adjacents, &n_adjacents);
                for (i = 0; i < n_adjacents; i++) {
                    if (labels_DFS[adjacents[i]] == LABEL_UNKNOWN) {
                        labels_DFS[adjacents[i]] = LABEL_DISCOVERED;
                        stack_DFS[stack_DFS_i++] = adjacents[i];
                        break;
                    }
                }
                if (stack_DFS_i_aux != stack_DFS_i) {
                    continue;
                }
                labels_DFS[actual_vertex] = LABEL_EXPLORED;
                --stack_DFS_i;
                stack_global[stack_global_i++] = actual_vertex;
            }
        }
    }

    for (vertex = 0; vertex < ((*graph).n_vertexes); vertex++) {
        labels_DFS[vertex] = LABEL_UNKNOWN;
    }

    while (stack_global_i > 0) {
        vertex = stack_global[--stack_global_i];
        if (labels_DFS[vertex] == LABEL_UNKNOWN) {
            group_id++;
            labels_DFS[vertex] = LABEL_DISCOVERED;
            stack_DFS_i = 0;
            stack_DFS[stack_DFS_i++] = vertex;
            while (stack_DFS_i > 0) {
                actual_vertex = stack_DFS[stack_DFS_i-1];
                stack_DFS_i_aux = stack_DFS_i;
                Graph_vertex_predecessors(graph, actual_vertex, &adjacents, &n_adjacents);
                for (i = 0; i < n_adjacents; i++) {
                    if (labels_DFS[adjacents[i]] == LABEL_UNKNOWN) {
                        labels_DFS[adjacents[i]] = LABEL_DISCOVERED;
                        stack_DFS[stack_DFS_i++] = adjacents[i];
                        break;
                    }
                }
                if (stack_DFS_i_aux != stack_DFS_i) {
                    continue;
                }
                labels_DFS[actual_vertex] = LABEL_EXPLORED;
                --stack_DFS_i;
                (*strongly_connected_components)[actual_vertex] = group_id;
            }
        }
    }

    free(stack_global);
    free(stack_DFS);
    free(labels_DFS);
}

