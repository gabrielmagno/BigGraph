CC = gcc
 
CFLAGS = -Wall

INC = -Isrc/

NAME_ALGORITHMS = reciprocity clustering_coefficient pagerank weakly_connected_components strongly_connected_components

OBJS_GRAPH = build/graph_graph.o
OBJS_ALGORITHM = $(NAME_ALGORITHMS:%=build/algorithm_%.o)

OBJ_SIZE = build/general_size.o
OBJ_PRINT = build/general_print.o
OBJ_ALGORITHMS = build/general_algorithms.o

BIN_SIZE = bin/size
BIN_PRINT = bin/print
BIN_ALGORITHMS = bin/algorithms

all: $(BIN_SIZE) $(BIN_PRINT) $(BIN_ALGORITHMS)

$(BIN_SIZE): $(OBJ_SIZE) $(OBJS_GRAPH) 
	$(CC) $(INC) $(CFLAGS) $(OBJS_GRAPH) $< -o $@

$(BIN_PRINT): $(OBJ_PRINT) $(OBJS_GRAPH) 
	$(CC) $(INC) $(CFLAGS) $(OBJS_GRAPH) $< -o $@

$(BIN_ALGORITHMS): $(OBJ_ALGORITHMS) $(OBJS_ALGORITHM) $(OBJS_GRAPH) 
	$(CC) $(INC) $(CFLAGS) $(OBJS_GRAPH) $(OBJS_ALGORITHM) $< -o $@

build/graph_%.o: src/graph/%.c src/graph/%.h
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

build/algorithm_%.o: src/algorithm/%.c src/algorithm/%.h
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

build/general_%.o: src/%.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

clean:
	rm -f build/* bin/*
