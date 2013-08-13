#include "strongly_connected_components.h"

void Graph_calculate_StronglyConnectedComponents(Graph * graph, unsigned int ** strongly_connected_components)
{
    /* Find the strongly connected components using Kosaraju's algorithm */

    Vertex_id vertex, actual_vertex;
    Vertex_id * adjacents, * stack_global, * stack_DFS;
    unsigned int i, n_adjacents, stack_global_i = 0, stack_DFS_i, group_id = 0, stack_DFS_i_aux;
    char * labels_DFS;
    
    stack_global = (Vertex_id *) malloc((100*(*graph).n_vertexes)*sizeof(Vertex_id));
    stack_DFS = (Vertex_id *) malloc(((*graph).n_vertexes)*sizeof(Vertex_id));
    labels_DFS = (char *) malloc(((*graph).n_vertexes)*sizeof(char));
    
    // Put each vertex into the null component (group_id = 0)
    // Initialize the depth-first search labels
    for (vertex = 0; vertex < ((*graph).n_vertexes); vertex++) {
        (*strongly_connected_components)[vertex] = 0;
        labels_DFS[vertex] = LABEL_UNKNOWN;
    }
    
    // For each vertex not yet labeled in DFS
    for (vertex = 0; vertex < ((*graph).n_vertexes); vertex++) {
        if (labels_DFS[vertex] == LABEL_UNKNOWN) {
            
            // Start DFS at vertex, by creating a DFS stack with the vertex inside
            labels_DFS[vertex] = LABEL_DISCOVERED;
            stack_DFS_i = 0;
            stack_DFS[stack_DFS_i++] = vertex;

            // While DFS stack is not empty 
            while (stack_DFS_i > 0) {

                // Get the top vertex in the stack (actual vertex)
                actual_vertex = stack_DFS[stack_DFS_i-1];

                // For each successor not yet labeled, 
                // label it as discovered, insert it into the DFS stack and
                // continue the DFS loop from it
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

                // If all the successors of actual vertex have already been explored,
                // label it as explored, remove it from the DFS stack and
                // insert it into the global stack
                labels_DFS[actual_vertex] = LABEL_EXPLORED;
                --stack_DFS_i;
                stack_global[stack_global_i++] = actual_vertex;

            }

        }
    }

    // Re-initialize the depth-first search labels
    for (vertex = 0; vertex < ((*graph).n_vertexes); vertex++) {
        labels_DFS[vertex] = LABEL_UNKNOWN;
    }

    // For each vertex in the global stack not yet labeled in DFS
    while (stack_global_i > 0) {
        vertex = stack_global[--stack_global_i];
        if (labels_DFS[vertex] == LABEL_UNKNOWN) {

            // Create a new component (next group id available)
            group_id++;
            
            // Start DFS at vertex, by creating a DFS stack with the vertex inside
            labels_DFS[vertex] = LABEL_DISCOVERED;
            stack_DFS_i = 0;
            stack_DFS[stack_DFS_i++] = vertex;

            // While DFS stack is not empty 
            while (stack_DFS_i > 0) {

                // Get the top vertex in the stack (actual vertex)
                actual_vertex = stack_DFS[stack_DFS_i-1];

                // For each predecessor not yet labeled, 
                // label it as discovered, insert it into the DFS stack and
                // continue the DFS loop from it
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

                // If all the predecessors of actual vertex have already been explored,
                // label it as explored, remove it from the DFS stack and
                // put it into the actual component
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

