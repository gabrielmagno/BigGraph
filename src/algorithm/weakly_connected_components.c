#include "weakly_connected_components.h"

void Graph_calculate_WeaklyConnectedComponents(Graph * graph, unsigned int ** weakly_connected_components)
{
    Vertex_id vertex, actual_vertex;
    Vertex_id * queue, * predecessors, * successors;
    unsigned int i, group_id = 0, n_predecessors, n_successors, queue_i, queue_j; 
    queue = (Vertex_id *) malloc(((*graph).n_vertexes)*sizeof(Vertex_id));
    for (vertex = 0; vertex < ((*graph).n_vertexes); vertex++) {
        (*weakly_connected_components)[vertex] = 0;
    }
    for (vertex = 0; vertex < ((*graph).n_vertexes); vertex++) {
        if ((*weakly_connected_components)[vertex] == 0) {
            queue_i = queue_j = 0;
            (*weakly_connected_components)[vertex] = ++group_id;
            queue[queue_j++] = vertex;
            while (queue_i < queue_j) {
                actual_vertex = queue[queue_i++];
                Graph_vertex_successors(graph, actual_vertex, &successors, &n_successors);
                Graph_vertex_predecessors(graph, actual_vertex, &predecessors, &n_predecessors);
                for (i = 0; i < n_successors; i++) {
                    if ((*weakly_connected_components)[successors[i]] == 0) {
                        (*weakly_connected_components)[successors[i]] = group_id;
                        queue[queue_j++] = successors[i];
                    }
                }
                for (i = 0; i < n_predecessors; i++) {
                    if ((*weakly_connected_components)[predecessors[i]] == 0) {
                        (*weakly_connected_components)[predecessors[i]] = group_id;
                        queue[queue_j++] = predecessors[i];
                    }
                }
            }
        }
    }
    free(queue);
}

