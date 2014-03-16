#include "reach.h"

void Graph_calculate_Reach(Graph * graph, int n_hops, unsigned int ** reach)
{
    Vertex_id vertex;

    // Config OpenMP
    omp_set_num_threads(omp_get_max_threads());

    #pragma omp parallel
    {
        Vertex_id actual_vertex;
        Vertex_id * predecessors, * stack_actual, * stack_next, * stack_temp;
        unsigned int i, n_predecessors, stack_actual_i, stack_next_i, level;
        char * distance;

        stack_actual = (Vertex_id *) malloc(((*graph).n_vertexes)*sizeof(Vertex_id));
        stack_next = (Vertex_id *) malloc(((*graph).n_vertexes)*sizeof(Vertex_id));
        distance = (char *) malloc(((*graph).n_vertexes)*sizeof(char));

        #pragma omp for
        for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {

            //for (actual_vertex = 0; actual_vertex < (*graph).n_vertexes; actual_vertex++) {
            //    distance[actual_vertex] = 0;
            //}
            memset(distance, 0, ((*graph).n_vertexes)*sizeof(char));

            level = 0;
            distance[vertex] = level + 1;

            stack_actual_i = 0;
            stack_actual[stack_actual_i++] = vertex;

            while ((level < n_hops) && (stack_actual_i > 0)) {
                
                level++;

                stack_next_i = 0;

                while (stack_actual_i > 0) {

                    actual_vertex = stack_actual[--stack_actual_i];

                    Graph_vertex_predecessors(graph, actual_vertex, &predecessors, &n_predecessors);
                    for (i = 0; i < n_predecessors; i++) {
                        if (distance[predecessors[i]] == 0) {
                            distance[predecessors[i]] = level + 1;
                            stack_next[stack_next_i++] = predecessors[i];
                        }
                    }

                }

                stack_temp = stack_actual;
                stack_actual = stack_next;
                stack_next = stack_temp;
                stack_actual_i = stack_next_i;

            }

            (*reach)[vertex] = 0;
            for (actual_vertex = 0; actual_vertex < (*graph).n_vertexes; actual_vertex++) {
                if (distance[actual_vertex] > 1) {
                    ((*reach)[vertex])++;
                }
            }

        }

        free(stack_actual);
        free(stack_next);
        free(distance);
    }

}

