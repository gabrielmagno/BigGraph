CC = gcc
 
CFLAGS = -Wall -O3

INC = -Isrc/

NAME_ALGORITHMS = reciprocity clustering_coefficient pagerank weakly_connected_components strongly_connected_components

OBJS_GRAPH = build/graph_graph.o
OBJS_ALGORITHM = $(NAME_ALGORITHMS:%=build/algorithm_%.o)
OBJS_ALGORITHM_OMP = $(NAME_ALGORITHMS:%=build/algorithmomp_%.o)
OBJS_ECCENTRICITY = build/algorithm_eccentricity.o

OBJ_SIZE = build/general_size.o
OBJ_PRINT = build/general_print.o
OBJ_ALGORITHMS = build/general_algorithms.o
OBJ_ECCENTRICITY = build/general_eccentricity.o

BIN_SIZE = bin/size
BIN_PRINT = bin/print
BIN_ALGORITHMS = bin/algorithms
BIN_ALGORITHMS_OMP = bin/algorithms_omp
BIN_ECCENTRICITY = bin/eccentricity

all: $(BIN_SIZE) $(BIN_PRINT) $(BIN_ALGORITHMS) $(BIN_ALGORITHMS_OMP) $(BIN_ECCENTRICITY) 

$(BIN_SIZE): $(OBJ_SIZE) $(OBJS_GRAPH) 
	$(CC) $(INC) $(CFLAGS) $(OBJS_GRAPH) $< -o $@

$(BIN_PRINT): $(OBJ_PRINT) $(OBJS_GRAPH) 
	$(CC) $(INC) $(CFLAGS) $(OBJS_GRAPH) $< -o $@

$(BIN_ALGORITHMS): $(OBJ_ALGORITHMS) $(OBJS_ALGORITHM) $(OBJS_GRAPH) 
	$(CC) $(INC) $(CFLAGS) $(OBJS_GRAPH) $(OBJS_ALGORITHM) $< -o $@

$(BIN_ALGORITHMS_OMP): $(OBJ_ALGORITHMS) $(OBJS_ALGORITHM_OMP) $(OBJS_GRAPH) 
	$(CC) $(INC) $(CFLAGS) -fopenmp $(OBJS_GRAPH) $(OBJS_ALGORITHM_OMP) $< -o $@

$(BIN_ECCENTRICITY): $(OBJ_ECCENTRICITY) $(OBJS_ECCENTRICITY) $(OBJS_GRAPH)
	$(CC) $(INC) $(CFLAGS) $(OBJS_GRAPH) $(OBJS_ECCENTRICITY) $< -o $@

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
