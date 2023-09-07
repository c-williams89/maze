#ifndef MATRIX_H
	#define MATRIX_H
	#include <stdio.h>
	#include <stdint.h>
	// typedef struct vertex_t vertex_t;
	typedef struct graph_t graph_t;
	graph_t *graph_create(void);
	graph_t * get_set_graph_size(FILE *fp, graph_t *graph);
	graph_t *matrix_graph_create(FILE *fp, graph_t *graph);
	void print_graph(graph_t *graph);
	// vertex_t **matrix_create(FILE *fp, uint16_t rows, uint16_t cols);
	// vertex_t **matrix_enrich(vertex_t **matrix, uint16_t rows, uint16_t cols);
	// void matrix_add_edge(vertex_t *current, vertex_t *neighbor);
#endif



