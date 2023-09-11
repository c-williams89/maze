#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Opaque data type to interact with graph. 
 */
typedef struct graph_t graph_t;

/**
 * @brief Creates graph.
 * 
 * @param valid_chars Array of valid characters that may appear in the map.
 * 
 * @return Pointer to graph on success, NULL on failure. 
 */
graph_t *graph_create(char *valid_chars);

/**
 * @brief Determines size of maze and sets graph variables.
 * 
 * @param fp Valid file pointer containing maze.
 * @param graph Pointer to graph to update.
 * 
 * @return 1 on success, 0 on failure
 */
int get_set_graph_size(FILE * fp, graph_t * graph);

/**
 * @brief Creates the matrix as part of the graph.
 * 
 * @param fp Valid file pointer containing maze.
 * @param graph Pointer to graph to add matrix to.
 * 
 * @return 1 on success, 0 on failure.
 */
int matrix_graph_create(FILE * fp, graph_t * graph);

/**
 * @brief Updates matrix vertices and sets member variables.
 * 
 * @param graph Pointer to graph containing matrix.
 * 
 * @return 1 on success, 0 on failure. 
 */
int matrix_enrich(graph_t * graph);

/**
 * @brief Validates maze is fully enclosed.
 * 
 * @param graph Pointer to graph containing matrix
 * 
 * @return true if valid, else false.  
 */
bool matrix_validate_maze(graph_t * graph);

/**
 * @brief Finds shortest path using Dijkstra's algorithm
 * 
 * @param graph Pointer to graph containing matrix.
 * 
 * @return 1 if path found, else 0. 
 */
int dijkstra_search(graph_t * graph);

/**
 * @brief Prints maze with path if valid maze with path found.
 * 
 * @param graph Pointer to graph containing matrix.
 */
void print_solved(graph_t * graph);

/**
 * @brief free() graph and members.
 * 
 * @param graph Pointer to graph to free(). 
 */
void matrix_destroy(graph_t * graph);

// Possibly unnecessary...
void print_graph(graph_t * graph);
#endif
