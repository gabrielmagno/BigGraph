#include <stdio.h>

#include "graph/graph.h"
#include "algorithm/distances.h"

int main(int argc, char * argv[])
{
    Graph graph;
    
    unsigned int n_selected, distance;
    unsigned int * distances_frequency;
    
    FILE * infile, * outfile;

    n_selected = (argc >= 2) ? atoi(argv[1])       : 0;
    infile     = (argc >= 3) ? fopen(argv[2], "r") : stdin;
    outfile    = (argc >= 4) ? fopen(argv[3], "w") : stdout;

    Graph_open(&graph, infile);
    if (argc >= 3) {
        fclose(infile);
    }

    distances_frequency = (unsigned int *) malloc((graph.n_vertexes + 1)*sizeof(unsigned int));
    
    Graph_calculate_Distances(&graph, n_selected, &distances_frequency);

    for (distance = 0; distance < (graph.n_vertexes + 1); distance++) {
        fprintf(outfile, "%d %d\n", distance, distances_frequency[distance]);
    }
    if (argc >= 4) {
        fclose(outfile);
    }
   
    Graph_close(&graph);

    free(distances_frequency);
    
    return EXIT_SUCCESS;
}

