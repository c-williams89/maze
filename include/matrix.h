#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
typedef struct graph_t graph_t;
graph_t *graph_create(char * valid_chars);
void matrix_destroy(graph_t * graph);
int get_set_graph_size(FILE * fp, graph_t * graph);
int matrix_graph_create(FILE * fp, graph_t * graph);
int matrix_enrich(graph_t * graph);
void print_graph(graph_t * graph);
int bfs(graph_t * graph);
void print_solved(graph_t * graph);
void add_valid_char (graph_t *graph, char flag);
bool matrix_validate_maze(graph_t * graph);
#endif
