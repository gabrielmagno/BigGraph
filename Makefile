CC = gcc
 
CFLAGS = -Wall

NAME_ALGORITHMS = reciprocity clustering_coefficient pagerank
NAME_AUX = print size

BIN_ALGORITHM = $(NAME_ALGORITHMS:%=bin/%)
BIN_ALGORITHM_OMP = $(NAME_ALGORITHMS:%=bin/%_OMP)
BIN_AUX = $(NAME_AUX:%=bin/%)

all: $(BIN_ALGORITHM) $(BIN_ALGORITHM_OMP) $(BIN_AUX)

bin/%_OMP: src/%_OMP.c src/graph.c src/graph.h 
	@echo "+ Compiling (OMP) \"$<\" in \"$@\""
	@$(CC) $(CFLAGS) -fopenmp src/graph.c $< -o $@

bin/%: src/%.c src/graph.c src/graph.h 
	@echo "+ Compiling \"$<\" in \"$@\""
	@$(CC) $(CFLAGS) src/graph.c $< -o $@

clean:
	rm -f bin/*
