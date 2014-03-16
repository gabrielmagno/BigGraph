CC = gcc
 
CFLAGS = -Wall -O3

INC = -Isrc/

NAME_ALGORITHMS = reciprocity clustering_coefficient pagerank weakly_connected_components strongly_connected_components

OBJS_GRAPH = build/graph_graph.o
OBJS_ALGORITHM = $(NAME_ALGORITHMS:%=build/algorithm_%.o)
OBJS_ALGORITHM_OMP = $(NAME_ALGORITHMS:%=build/algorithmomp_%.o)
OBJS_DISTANCES = build/algorithm_distances.o
OBJS_DISTANCES_OMP = build/algorithmomp_distances.o
OBJS_REACH = build/algorithm_reach.o
OBJS_REACH_OMP = build/algorithmomp_reach.o

OBJ_SIZE = build/general_size.o
OBJ_PRINT = build/general_print.o
OBJ_ALGORITHMS = build/general_algorithms.o
OBJ_DISTANCES = build/general_distances.o
OBJ_REACH = build/general_reach.o

BIN_SIZE = bin/size
BIN_PRINT = bin/print
BIN_ALGORITHMS = bin/algorithms
BIN_ALGORITHMS_OMP = bin/algorithms_omp
BIN_DISTANCES = bin/distances
BIN_DISTANCES_OMP = bin/distances_omp
BIN_REACH = bin/reach
BIN_REACH_OMP = bin/reach_omp


all: $(BIN_SIZE) $(BIN_PRINT) $(BIN_ALGORITHMS) $(BIN_ALGORITHMS_OMP) $(BIN_DISTANCES) $(BIN_DISTANCES_OMP) $(BIN_REACH) $(BIN_REACH_OMP)

$(BIN_SIZE): $(OBJ_SIZE) $(OBJS_GRAPH) 
	$(CC) $(INC) $(CFLAGS) $(OBJS_GRAPH) $< -o $@

$(BIN_PRINT): $(OBJ_PRINT) $(OBJS_GRAPH) 
	$(CC) $(INC) $(CFLAGS) $(OBJS_GRAPH) $< -o $@

$(BIN_ALGORITHMS): $(OBJ_ALGORITHMS) $(OBJS_ALGORITHM) $(OBJS_GRAPH) 
	$(CC) $(INC) $(CFLAGS) $(OBJS_GRAPH) $(OBJS_ALGORITHM) $< -o $@

$(BIN_ALGORITHMS_OMP): $(OBJ_ALGORITHMS) $(OBJS_ALGORITHM_OMP) $(OBJS_GRAPH) 
	$(CC) $(INC) $(CFLAGS) -fopenmp $(OBJS_GRAPH) $(OBJS_ALGORITHM_OMP) $< -o $@

$(BIN_DISTANCES): $(OBJ_DISTANCES) $(OBJS_DISTANCES) $(OBJS_GRAPH)
	$(CC) $(INC) $(CFLAGS) $(OBJS_GRAPH) $(OBJS_DISTANCES) $< -o $@

$(BIN_DISTANCES_OMP): $(OBJ_DISTANCES) $(OBJS_DISTANCES_OMP) $(OBJS_GRAPH)
	$(CC) $(INC) $(CFLAGS) -fopenmp $(OBJS_GRAPH) $(OBJS_DISTANCES_OMP) $< -o $@

$(BIN_REACH): $(OBJ_REACH) $(OBJS_REACH) $(OBJS_GRAPH)
	$(CC) $(INC) $(CFLAGS) $(OBJS_GRAPH) $(OBJS_REACH) $< -o $@

$(BIN_REACH_OMP): $(OBJ_REACH) $(OBJS_REACH_OMP) $(OBJS_GRAPH)
	$(CC) $(INC) $(CFLAGS) -fopenmp $(OBJS_GRAPH) $(OBJS_REACH_OMP) $< -o $@


build/graph_%.o: src/graph/%.c src/graph/%.h
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

build/algorithm_%.o: src/algorithm/%.c src/algorithm/%.h
	$(CC) $(INC) $(CFLAGS) -lm -c $< -o $@

build/algorithmomp_%.o: src/algorithm_omp/%.c src/algorithm_omp/%.h
	$(CC) $(INC) $(CFLAGS) -lm -fopenmp -c $< -o $@

build/general_%.o: src/%.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@


clean:
	rm -f build/* bin/*
