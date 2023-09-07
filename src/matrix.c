#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

#include "../include/llist.h"

enum { SPACE = 1, WALL = 11, WATER = 3, END = 1, START = 0 };

typedef struct vertex_t {
        struct vertex_t *parent;
        struct edge_t *neighbors;
        int value;
        char letter;
        int level;
        int num_children;
} vertex_t;


typedef struct edge_t {
        vertex_t *destination;
        struct edge_t *next;
} edge_t;

typedef struct graph_t {
        vertex_t **matrix;
        vertex_t *start;
        vertex_t *end;
        uint16_t rows;
        uint16_t cols;
} graph_t;

static void matrix_add_edge(vertex_t *current, vertex_t *neighbor);
static void bfs(vertex_t **matrix, vertex_t *start, vertex_t *end);

graph_t *graph_create(void) {
        graph_t *graph = calloc(1, sizeof(*graph));
        return graph;
}

graph_t * get_set_graph_size(FILE *fp, graph_t *graph) {
        if (!graph) {
                perror("get_graph_size: Error allocating memory\n");
                errno = 0;
                goto EXIT;
        }
        graph->cols = 0;
        graph->rows = 1;
        uint16_t cols = 0;
        char c = '\0';
        while ((c = fgetc(fp)) != EOF) {
                if ('\n' == c) {
                        if (cols > graph->cols) {
                                graph->cols = cols;
                        }
                        cols = 0;
                        graph->rows++;
                        continue;
                }
                ++cols;
        }
        rewind(fp);
EXIT:
        return graph;
}

// TODO: Don't need to return the graph from these.

graph_t *matrix_graph_create(FILE *fp, graph_t *graph) {
        graph->matrix = calloc(graph->rows, sizeof(vertex_t*));
        vertex_t  **matrix = calloc(graph->rows, sizeof(*matrix));
        graph->start = NULL;
        graph->end = NULL;
        char letter = '\0';

        for (int row = 0; row < graph->rows; ++row) {
                graph->matrix[row] = calloc(graph->cols, sizeof(vertex_t));
                // TODO: Added less than or equal to handle newline at end. Need a better way
                //  of finding newline and null terminating instead.
                for (int col = 0; col <= graph->cols; ++col) {
                        letter = fgetc(fp);
                        switch (letter)
                        {
                        case '@':
                                graph->start = graph->matrix[row] + col;
                                graph->start->level = INT_MAX;
                                graph->start->value = START;
                                break;
                        case '>':
                                graph->end = graph->matrix[row] + col;
                                graph->end->value = END;
                                break;
                        case '#':
                                graph->matrix[row][col].value = WALL;
                                break;
                        case '\n':
                                continue;
                                // break;
                        default:
                                // graph->matrix[row][col].letter = 28;
                                break;
                        }
                        graph->matrix[row][col].letter = letter;
                }
        }
        return graph;
}

void print_graph(graph_t *graph) {
        printf("Inside print graph\n");
        for (int row = 0; row < graph->rows; ++row) {
                for (int col = 0; col < graph->cols; ++col) {
                        printf("%c", graph->matrix[row][col].letter);
                }
                printf("\n");
        }
}

graph_t *matrix_enrich(graph_t *graph) {
        vertex_t *current = NULL;
        vertex_t *neighbor = NULL;

        int neighbor_x[] = {-1, 0, 1, 0};
        int neighbor_y[] = {0, 1, 0, -1};

        for (int row = 0; row < graph->rows; ++row) {
                for (int col = 0; col < graph->cols; ++col) {
                        current = &(graph->matrix[row][col]);
                        for (int i = 0; i < 4; ++i) {
                                int tgt_x = row + neighbor_x[i];
                                int tgt_y = col + neighbor_y[i];
                        
                                if ((tgt_x > -1) && (tgt_x < graph->rows) && (tgt_y > -1) && (tgt_y < graph->cols)) {
                                        neighbor = &(graph->matrix[tgt_x][tgt_y]);
                                        if (neighbor->value != 28) {
                                                // matrix_add_edge(current, neighbor);
                                        }
                                        current->num_children += 1;
                                }

                        }        
                }
        }
        return graph;
}

/*
// NOTE: This function could probably be static as well.
vertex_t **matrix_enrich(vertex_t **matrix, uint16_t rows, uint16_t cols) {
        vertex_t *current = NULL;
        vertex_t *neighbor = NULL;

        int neighbor_x[] = {-1, 0, 1, 0};
        int neighbor_y[] = {0, 1, 0, -1};

        for (int row = 0; row < rows; ++row) {
                for (int col = 0; col < cols; ++col) {
                        current = &(matrix[row][col]);
                        for (int i = 0; i < 4; ++i) {
                                int tgt_x = row + neighbor_x[i];
                                int tgt_y = col + neighbor_y[i];
                        
                                if ((tgt_x > -1) && (tgt_x < rows) && (tgt_y > -1) && (tgt_y < cols)) {
                                        neighbor = &(matrix[tgt_x][tgt_y]);
                                        if (neighbor->value != 28) {
                                                matrix_add_edge(current, neighbor);
                                        }
                                        current->num_children += 1;
                                }

                        }        
                }
        }
        return matrix;
}

static void matrix_add_edge(vertex_t *current, vertex_t *neighbor) {
        edge_t *new_edge = calloc(1, sizeof(*new_edge));

        new_edge->destination = neighbor;
        new_edge->next = current->neighbors;
        current->neighbors = new_edge;
}

static void bfs(vertex_t **matrix, vertex_t *start, vertex_t *end) {
        llist_t *queue = llist_create();
        llist_enqueue(queue, start);
        // TODO: For Djikstras, priority queue must be implemented here
        int level = 0;
        while(!llist_is_empty(queue)) {
                vertex_t *node = (vertex_t *)llist_dequeue(queue);          
                edge_t *current = node->neighbors;
                if (!current) {
                        return;
                }

                do {
                        if (!current->destination->level) {
                                current->destination->level = level + 1;
                                current->destination->parent = node;
                                llist_enqueue(queue, current->destination);
                        }
                        current = current->next;
                } while (current); 
                level += 1;
        }

        llist_t *stack = llist_create();
        vertex_t *node = end;
        int counter = 0;
        while (node != node->parent) {
                node->value = '+';
                llist_push(stack, node);
                node = node->parent;
                ++counter;
        }
        printf("From end to start: %d\n", counter);
} 
*/