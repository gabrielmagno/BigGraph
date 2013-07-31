#include "graph/graph.h"

#include "algorithm/reciprocity.h"
#include "algorithm/clustering_coefficient.h"
#include "algorithm/pagerank.h"
#include "algorithm/weakly_connected_components.h"
#include "algorithm/strongly_connected_components.h"

int main(int argc, char * argv[])
{
    Graph graph;
    Vertex_id vertex;
    
    double * reciprocity;
    double * clustering_coefficient;
    double * pagerank;
    unsigned int * weakly_connected_components;
    unsigned int * strongly_connected_components;

    FILE * outfile;

    Graph_open(&graph, argv[1]);

    reciprocity = (double *) malloc(graph.n_vertexes*sizeof(double));
    clustering_coefficient = (double *) malloc(graph.n_vertexes*sizeof(double));
    pagerank = (double *) malloc(graph.n_vertexes*sizeof(double));
    weakly_connected_components = (unsigned int *) malloc(graph.n_vertexes*sizeof(unsigned int));
    strongly_connected_components = (unsigned int *) malloc(graph.n_vertexes*sizeof(unsigned int));

    Graph_calculate_Reciprocity(&graph, &reciprocity);
    Graph_calculate_ClusteringCoefficient(&graph, &clustering_coefficient);
    Graph_calculate_PageRank(&graph, &pagerank, 1);
    Graph_calculate_WeaklyConnectedComponents(&graph, &weakly_connected_components);
    Graph_calculate_StronglyConnectedComponents(&graph, &strongly_connected_components);
    
    outfile = fopen(argv[2], "w");
    for (vertex = 0; vertex < graph.n_vertexes; vertex++) {
        fprintf(outfile, "%d %d %d %f %f %f %d %d\n", vertex, graph.vertexes[vertex].in_degree,
                                                             graph.vertexes[vertex].out_degree,
                                                             reciprocity[vertex],
                                                             clustering_coefficient[vertex],
                                                             pagerank[vertex],
                                                             weakly_connected_components[vertex],
                                                             strongly_connected_components[vertex]);
    }
    fclose(outfile);
    
    Graph_close(&graph);

    free(reciprocity);
    free(clustering_coefficient);
    free(pagerank);
    free(weakly_connected_components);
    free(strongly_connected_components);

    return EXIT_SUCCESS;
}

