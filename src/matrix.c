#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

enum { SPACE = 1, WALL = 11, WATER = 3 };

typedef struct vertex_t {
        struct vertex_t *parent;
        struct edge_t *neighbors;
        char value;
        int level;
        int num_children;
} vertex_t;

typedef struct edge_t {
        vertex_t *destination;
        struct edge_t *next;
} edge_t;
static void matrix_add_edge(vertex_t *current, vertex_t *neighbor);

vertex_t **matrix_create(FILE *fp, uint16_t rows, uint16_t cols) {
        // TODO: Possible boolean to track valid/invalid map?
        vertex_t **matrix = calloc(rows, sizeof(*matrix));
        if (!matrix) {
                fprintf(stderr, "matrix_create: Unable to allocate memory\n");
                return NULL;
        }
        vertex_t *start = NULL;
        vertex_t *end = NULL;

        char letter = '\0';
        for (int row = 0; row < rows; ++row) {
                matrix[row] = calloc(cols, sizeof(vertex_t));

                for (int col = 0; col < cols; ++col) {
                        letter = fgetc(fp);
                        switch (letter)
                        {
                        case '@':
                                if (start) {
                                        matrix = NULL;
                                        goto EXIT;
                                }
                                // (matrix[row] + col)->level = INT_MAX;
                                start = matrix[row] + col;
                                start->level = INT_MAX;
                                break;                        
                        case '>':
                                end = matrix[row] + col;
                                break;
                        case '#':
                                matrix[row][col].value = WALL;
                                break;
                        // TODO: find empty spaces and set to ASCII dec 28
                        case '\n':
                                continue;
                        // default:
                                // matrix = NULL;
                                // goto EXIT;
                        }

                        // matrix[row][col].value = 1;
                }
        }

EXIT:
        return matrix;
}

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