#include <stdio.h>
#include <sys/time.h>

#include "graph/graph.h"
#include "algorithm/reach.h"

int main(int argc, char * argv[])
{
    Graph graph;
    Vertex_id vertex;
    
    unsigned int * reach;

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

    reach = (unsigned int *) malloc(graph.n_vertexes*sizeof(unsigned int));

    Graph_calculate_Reach(&graph, 2, &reach);
   
    if (argc >= 3) {
        outfile = fopen(argv[2], "w");
    }
    else {
        outfile = stdout;
    }

    for (vertex = 0; vertex < graph.n_vertexes; vertex++) {
        fprintf(outfile, "%d %d\n", vertex, reach[vertex]);
    }

    if (argc >= 3) {
        fclose(outfile);
    }
   
    Graph_close(&graph);
    
    free(reach);

    return EXIT_SUCCESS;

}

