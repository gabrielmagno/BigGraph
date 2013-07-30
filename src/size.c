#include <stdio.h>
#include "graph/graph.h"

void bytes_readable(unsigned long long int n_bytes, double * n, char * s)
{
    static char magnitude[] = " KMGT";
    int i = 0;
    *n = (double) n_bytes;
    while ((*n) > 1024.0) {
        (*n) /= 1024.0;
        i++;
    }
    *s = magnitude[i];
}

int main(int argc, char * argv[])
{
    unsigned long long int n_vertexes, n_edges, size_graph;
    double n_bytes;
    char s_bytes;

    /* Read Graph */
    scanf("%lld", &n_vertexes);
    scanf("%lld", &n_edges);

    /* Calculate Size */
    size_graph = n_vertexes*sizeof(Vertex) + n_edges*sizeof(Vertex_id) + n_edges*sizeof(Vertex_id);

    /* Print results */
    printf("---------- System ----------\n");
    printf("* int = %lu\n", ((unsigned long) sizeof(int)));
    printf("* unsigned int = %lu\n", ((unsigned long) sizeof(unsigned int)));
    printf("* float = %lu\n", ((unsigned long) sizeof(float)));
    printf("* long long int = %lu\n", ((unsigned long) sizeof(long long int)));
    printf("* double = %lu\n", ((unsigned long) sizeof(double)));
    printf("---------- Graph ----------\n");
    printf("* Vertexes: %'lld\n", n_vertexes);
    printf("* Edges: %'lld\n", n_edges);
    bytes_readable(size_graph, &n_bytes, &s_bytes);
    printf("    - Graph in memory: %lld B (%.1f %cB)\n", size_graph, n_bytes, s_bytes);
    bytes_readable(n_vertexes, &n_bytes, &s_bytes);
    printf("    - Additional vertex information: %lld / B (%.1f %cB)\n", n_vertexes, n_bytes, s_bytes);
    bytes_readable(n_edges, &n_bytes, &s_bytes);
    printf("    - Additional edge information: %lld / B (%.1f %cB)\n", n_edges, n_bytes, s_bytes);
    printf("------------------------------\n");

    return EXIT_SUCCESS;
}

