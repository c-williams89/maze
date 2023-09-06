#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>




typedef struct vertex_t {
        struct vertex *parent;
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
        return NULL;
}