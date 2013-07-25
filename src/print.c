#include <stdio.h>
#include "graph.h"

int main(int argc, char * argv[])
{
    Graph grafo;
    Graph_open(&grafo, NULL);
    Graph_print(&grafo, NULL);
    Graph_print_matrix(&grafo, NULL);
    Graph_print_friends(&grafo, NULL);
    Graph_close(&grafo);
    return EXIT_SUCCESS;
}

