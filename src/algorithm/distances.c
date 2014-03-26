#include "distances.h"

void Graph_calculate_Distances(Graph * graph, unsigned int n_selected, unsigned int ** distances_frequency)
{
    Vertex_id vertex_random, vertex, actual_vertex;
    Vertex_id * selected, * successors, * stack_actual, * stack_next, * stack_temp;
    char * marked;
    unsigned int infinity, i_selected, distance, i, n_successors, stack_actual_i, stack_next_i, level;
    unsigned int * distances;
    
    infinity = (*graph).n_vertexes + 1;

    if ((n_selected == 0) || (n_selected > ((*graph).n_vertexes))) {
        n_selected = (*graph).n_vertexes; 
    }

    selected = (Vertex_id *) malloc((n_selected)*sizeof(Vertex_id));
    marked = (char *) malloc(((*graph).n_vertexes)*sizeof(char));

    stack_actual = (Vertex_id *) malloc(((*graph).n_vertexes)*sizeof(Vertex_id));
    stack_next = (Vertex_id *) malloc(((*graph).n_vertexes)*sizeof(Vertex_id));
    distances = (unsigned int *) malloc(((*graph).n_vertexes)*sizeof(unsigned int));

    // Select vertexes that will have distances calculated
    if (n_selected < ((*graph).n_vertexes)) {

        // Random vertexes
        memset(marked, 0, ((*graph).n_vertexes)*sizeof(char));
        srand(time(NULL));
        i_selected = 0;
        while (i_selected < n_selected) {
            vertex_random = rand() % ((*graph).n_vertexes);
            if (! marked[vertex_random]) {
                marked[vertex_random] = 1;
                selected[i_selected++] = vertex_random;
            }
        }

    }
    else {

        // All vertexes
        for (i_selected = 0; i_selected < n_selected; i_selected++) {
            selected[i_selected] = i_selected;
        }

    }

    // Start distances counter 
    for (distance = 0; distance < ((*graph).n_vertexes + 1); distance++) {
        (*distances_frequency)[distance] = 0;
    }

    // For each selected vertex
    for (i_selected = 0; i_selected < n_selected; i_selected++) {
        vertex = selected[i_selected];

        // Set initial distance to all vertexes as infinity
        for (actual_vertex = 0; actual_vertex < (*graph).n_vertexes; actual_vertex++) {
            distances[actual_vertex] = infinity;
        }

        // Set self-distance as zero
        level = 0;
        distances[vertex] = level;

        // Start stack with the original vertex
        stack_actual_i = 0;
        stack_actual[stack_actual_i++] = vertex;

        // While there are vertexes to explore 
        while (stack_actual_i > 0) {
            
            // Increase level (distance from original vertex)
            level++;

            // Empty next-level stack
            stack_next_i = 0;

            // While there are vertexes to explore in the actual level
            while (stack_actual_i > 0) {
                actual_vertex = stack_actual[--stack_actual_i];

                // For each successor not yet reached,
                Graph_vertex_successors(graph, actual_vertex, &successors, &n_successors);
                for (i = 0; i < n_successors; i++) {
                    if (distances[successors[i]] == infinity) {

                        // Set distance as the actual level
                        distances[successors[i]] = level;

                        // Insert successor in the next-level stack
                        stack_next[stack_next_i++] = successors[i];

                    }
                }

            }

            // Swap stacks
            stack_temp = stack_actual;
            stack_actual = stack_next;
            stack_next = stack_temp;
            stack_actual_i = stack_next_i;

        }
        
        for (actual_vertex = 0; actual_vertex < (*graph).n_vertexes; actual_vertex++) {
            (*distances_frequency)[distances[actual_vertex]] += 1;
        }

    }

    free(selected);
    free(marked);
    free(stack_actual);
    free(stack_next);
    free(distances);
}

