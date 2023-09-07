#ifndef MATRIX_H
	#define MATRIX_H
	#include <stdio.h>
	#include <stdint.h>
	typedef struct vertex_t vertex_t;
	vertex_t **matrix_create(FILE *fp, uint16_t rows, uint16_t cols);
	vertex_t **matrix_enrich(vertex_t **matrix);
#endif


