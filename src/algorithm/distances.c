#include "distances.h"

void Graph_calculate_Distances(Graph * graph, FILE * outfile)
{
    Vertex_id vertex, actual_vertex;
    Vertex_id * successors, * stack_actual, * stack_next, * stack_temp;
    unsigned int i, n_successors, stack_actual_i, stack_next_i, level, infinity, max_distance;
    unsigned int * distance;

    infinity = (*graph).n_vertexes + 1;
   
    stack_actual = (Vertex_id *) malloc(((*graph).n_vertexes)*sizeof(Vertex_id));
    stack_next = (Vertex_id *) malloc(((*graph).n_vertexes)*sizeof(Vertex_id));
    distance = (unsigned int *) malloc(((*graph).n_vertexes)*sizeof(unsigned int));

    for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {

        for (actual_vertex = 0; actual_vertex < (*graph).n_vertexes; actual_vertex++) {
            distance[actual_vertex] = infinity;
        }

        level = 0;
        distance[vertex] = level;

        stack_actual_i = 0;
        stack_actual[stack_actual_i++] = vertex;

        while (stack_actual_i > 0) {
            
            level++;

            stack_next_i = 0;

            while (stack_actual_i > 0) {

                actual_vertex = stack_actual[--stack_actual_i];

                Graph_vertex_successors(graph, actual_vertex, &successors, &n_successors);
                for (i = 0; i < n_successors; i++) {
                    if (distance[successors[i]] == infinity) {
                        distance[successors[i]] = level;
                        stack_next[stack_next_i++] = successors[i];
                    }
                }

            }

            stack_temp = stack_actual;
            stack_actual = stack_next;
            stack_next = stack_temp;
            stack_actual_i = stack_next_i;

        }
        
        for (actual_vertex = 0; actual_vertex < (*graph).n_vertexes; actual_vertex++) {
            if((vertex != actual_vertex) && (distance[actual_vertex] != infinity)) {
                fprintf(outfile, "%d %d %d\n", vertex, actual_vertex, distance[actual_vertex]);
            }
        }
        fflush(outfile);

    }

    free(stack_actual);
    free(stack_next);
    free(distance);
}

