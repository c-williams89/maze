#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

enum { SPACE = 1, WALL = 11, WATER = 3 };

typedef struct vertex_t {
        struct vertex_t *parent;
        struct edge *neighbors;
        char value;
        int level;
        int num_children;
} vertex_t;

typedef struct edge {
        vertex_t *destination;
        struct edge *next;
} edge;

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
                        case '\n':
                                continue;
                        // default:
                                // matrix = NULL;
                                // goto EXIT;
                        }

                        matrix[row][col].value = 1;
                }
        }

EXIT:
        return matrix;
}

vertex_t **matrix_enrich(vertex_t **matrix) {
        return NULL;
}