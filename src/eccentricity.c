#include <stdio.h>

#include "graph/graph.h"
#include "algorithm/eccentricity.h"

int main(int argc, char * argv[])
{
    Graph graph;
    Vertex_id vertex;
    
    unsigned int * eccentricity;
    FILE * infile, * outfile;

    if (argc >= 2) {
        infile = fopen(argv[1], "r");
    }
    else {
        infile = stdin;
    }
    Graph_open(&graph, infile);
    if (argc >= 2) {
        fclose(infile);
    }

    eccentricity = (unsigned int *) malloc(graph.n_vertexes*sizeof(unsigned int));

    Graph_calculate_Eccentricity(&graph, &eccentricity);

    if (argc >= 3) {
        outfile = fopen(argv[2], "w");
    }
    else {
        outfile = stdout;
    }
    for (vertex = 0; vertex < graph.n_vertexes; vertex++) {
        fprintf(outfile, "%d %d\n", vertex, eccentricity[vertex]);
    }
    if (argc >= 3) {
        fclose(outfile);
    }
    
    Graph_close(&graph);
    
    free(eccentricity);

    return EXIT_SUCCESS;
}

