#include <stdio.h>
#include "graph/graph.h"

int main(int argc, char * argv[])
{
    Graph graph;
    
    FILE * infile, * outfile;

    // Get input file
    if (argc >= 2) {
        infile = fopen(argv[1], "r");
    }
    else {
        infile = stdin;
    }

    // Ge output file
    if (argc >= 3) {
        outfile = fopen(argv[2], "w");
    }
    else {
        outfile = stdout;
    }
   
    // Read graph
    Graph_open(&graph, infile);
    if (argc >= 2) {
        fclose(infile);
    }

    // Output graph
    Graph_print(&graph, outfile);
    Graph_print_matrix(&graph, outfile);
    Graph_print_friends(&graph, outfile);
    Graph_print_neighbours(&graph, outfile);

    // Free graph
    Graph_close(&graph);
    if (argc >= 3) {
        fclose(outfile);
    }

    return EXIT_SUCCESS;
}

