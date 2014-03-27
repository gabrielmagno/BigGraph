#include <stdio.h>

#include "graph/graph.h"
#include "algorithm/distances.h"

int main(int argc, char * argv[])
{
    Graph graph;
    
    unsigned int n_selected, distance;
    unsigned long long int * dists_freq_directed, * dists_freq_undirected;
    
    FILE * infile, * outfile;

    n_selected = (argc >= 2) ? atoi(argv[1])       : 0;
    infile     = (argc >= 3) ? fopen(argv[2], "r") : stdin;
    outfile    = (argc >= 4) ? fopen(argv[3], "w") : stdout;

    Graph_open(&graph, infile);
    if (argc >= 3) {
        fclose(infile);
    }

    dists_freq_directed = (unsigned long long int *) malloc((graph.n_vertexes + 1)*sizeof(unsigned long long int));
    dists_freq_undirected = (unsigned long long int *) malloc((graph.n_vertexes + 1)*sizeof(unsigned long long int));
    
    Graph_calculate_Distances(&graph, n_selected, 0, &dists_freq_directed);
    Graph_calculate_Distances(&graph, n_selected, 1, &dists_freq_undirected);

    for (distance = 0; distance < (graph.n_vertexes + 1); distance++) {
        fprintf(outfile, "%d %lld %lld\n", distance, dists_freq_directed[distance], dists_freq_undirected[distance]);
    }
    if (argc >= 4) {
        fclose(outfile);
    }
   
    Graph_close(&graph);

    free(dists_freq_directed);
    free(dists_freq_undirected);
    
    return EXIT_SUCCESS;
}

