#include <stdio.h>

#include "graph/graph.h"
#include "algorithm/distances.h"

int main(int argc, char * argv[])
{
    Graph graph;
    Vertex_id vertex;
    
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

    if (argc >= 3) {
        outfile = fopen(argv[2], "w");
    }
    else {
        outfile = stdout;
    }
    Graph_calculate_Distances(&graph, outfile);
    if (argc >= 3) {
        fclose(outfile);
    }
   
    Graph_close(&graph);
    
    return EXIT_SUCCESS;
}

