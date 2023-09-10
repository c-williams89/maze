#include <check.h>
#include <stdio.h>
#include <limits.h>

#include "../include/matrix.h"

typedef struct vertex_t {
	struct vertex_t *parent;
	struct edge_t *neighbors;
	int value;
	int weight;
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
	uint16_t size;
} graph_t;

START_TEST(test_graph_create_valid)
{
     	FILE *fp = fopen("./data/valid_map.txt", "r");
     	graph_t *graph = graph_create();
//      vertex_t **matrix = matrix_create(fp, 83, 23);
//      ck_assert_int_eq((matrix[1] + 11)->level, INT_MAX);
	ck_assert_ptr_ne(graph, NULL);
//      ck_assert_ptr_ne(matrix, NULL);
} END_TEST 

START_TEST(test_get_set_graph_size) {
	// TODO: put these as part of setup function
     	FILE *fp = fopen("./data/valid_map.txt", "r");
	graph_t *graph = graph_create();
	if (get_set_graph_size(fp, graph)) {
		ck_assert_int_eq(graph->cols, 23);
		ck_assert_int_eq(graph->rows, 8);
	}
} END_TEST

START_TEST(test_get_set_graph_size_invalid) {
	FILE *fp = fopen("./data/invalid_map.txt", "r");
	graph_t *graph = graph_create();
	ck_assert_int_eq(get_set_graph_size(fp, graph), 0);
} END_TEST

// Tests matrix creates successfully and tests known values assigned to graph.
START_TEST(test_matrix_graph_create) {
	FILE *fp = fopen("./data/valid_map.txt", "r");
	graph_t *graph = graph_create();
	graph->rows = 8;
	graph->cols = 23;
	ck_assert_int_eq(matrix_graph_create(fp, graph), 1);
	ck_assert_ptr_ne(graph->start, NULL);
	ck_assert_ptr_ne(graph->end, NULL);
	vertex_t *start = &(graph)->matrix[2][15];
	vertex_t *end = &(graph)->matrix[2][4];
	ck_assert_ptr_eq(start, graph->start);
	ck_assert_ptr_eq(end, graph->end);
}END_TEST

START_TEST(test_matrix_graph_create_invalid) {
	FILE *fp = fopen("./data/invalid_graph.txt", "r");
	graph_t *graph = graph_create();
	graph->rows = 8;
	graph->cols = 23;
	ck_assert_int_eq(matrix_graph_create(fp, graph), 0);
}END_TEST

START_TEST(test_matrix_enrich) {
	FILE *fp = fopen("./data/valid_map.txt", "r");
	graph_t *graph = graph_create();
	graph->rows = 8;
	graph->cols = 23;
	matrix_graph_create(fp, graph);
	ck_assert_int_eq(matrix_enrich(graph), 1);
	ck_assert_ptr_ne(graph->start->neighbors, NULL);
	ck_assert_int_eq(graph->start->num_children, 1);
	ck_assert_int_eq(graph->end->num_children, 3);
	ck_assert_int_eq(graph->matrix[0][0].num_children, 2);
	vertex_t *start_neigh = &(graph)->matrix[2][16];
	ck_assert_ptr_eq(graph->start->neighbors->destination, start_neigh);
}END_TEST

static TFun core_tests[] = {
	test_graph_create_valid,
	test_get_set_graph_size,
	test_get_set_graph_size_invalid,
	test_matrix_graph_create,
	test_matrix_graph_create_invalid,
	test_matrix_enrich,
     NULL
};

Suite *test_matrix(void)
{
     Suite *s = suite_create("test_matrix");
     TFun *curr = NULL;
     TCase *tc_core = tcase_create("core");
     curr = core_tests;
     while (*curr) {
             tcase_add_test(tc_core, *curr++);
     }

     suite_add_tcase(s, tc_core);
     return s;
}
