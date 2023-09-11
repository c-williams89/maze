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
	bool path;
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

char valid_chars[] = "@ >";

START_TEST(test_graph_create)
{
	graph_t *graph = graph_create(valid_chars);
	ck_assert_ptr_ne(graph, NULL);
} END_TEST START_TEST(test_get_set_graph_size)
{
	FILE *fp = fopen("./test/test_data/valid_map.txt", "r");
	graph_t *graph = graph_create(valid_chars);
	if (get_set_graph_size(fp, graph)) {
		ck_assert_int_eq(graph->cols, 23);
		ck_assert_int_eq(graph->rows, 8);
	}
}

END_TEST START_TEST(test_get_set_graph_size_invalid)
{
	FILE *fp = fopen("./test/test_data/invalid_char.txt", "r");
	graph_t *graph = graph_create(valid_chars);
	ck_assert_int_eq(get_set_graph_size(fp, graph), 0);
}

END_TEST
// Tests matrix creates successfully and tests known values assigned to graph.
START_TEST(test_matrix_graph_create)
{
	FILE *fp = fopen("./test/test_data/valid_map.txt", "r");
	graph_t *graph = graph_create(valid_chars);
	graph->rows = 8;
	graph->cols = 23;
	ck_assert_int_eq(matrix_graph_create(fp, graph), 1);
	ck_assert_ptr_ne(graph->start, NULL);
	ck_assert_ptr_ne(graph->end, NULL);
	vertex_t *start = &(graph)->matrix[2][7];
	vertex_t *end = &(graph)->matrix[2][4];
	ck_assert_ptr_eq(start, graph->start);
	ck_assert_ptr_eq(end, graph->end);
}

END_TEST START_TEST(test_matrix_graph_create_invalid)
{
	const char *invalid_maps[] = {
		"./test/test_data/invalid_start_mult.txt",
		"./test/test_data/invalid_end_mult.txt"
	};

	for (int i = 0; i < 2; ++i) {
		FILE *fp = fopen(invalid_maps[i], "r");
		graph_t *graph = graph_create(valid_chars);
		graph->rows = 8;
		graph->cols = 23;
		ck_assert_int_eq(matrix_graph_create(fp, graph), 0);
	}
}

END_TEST START_TEST(test_matrix_enrich)
{
	FILE *fp = fopen("./test/test_data/valid_map.txt", "r");
	graph_t *graph = graph_create(valid_chars);
	graph->rows = 8;
	graph->cols = 23;
	matrix_graph_create(fp, graph);
	ck_assert_int_eq(matrix_enrich(graph), 1);
	ck_assert_ptr_ne(graph->start->neighbors, NULL);
	vertex_t *start_neigh = &(graph)->matrix[2][8];
	ck_assert_ptr_eq(graph->start->neighbors->destination, start_neigh);
} END_TEST START_TEST(test_matrix_validate_maze_invalid)
{
	const char *invalid_maps[] = {
		"./test/test_data/invalid_start.txt",
		"./test/test_data/invalid_end.txt"
	};

	for (int i = 0; i < 2; ++i) {
		FILE *fp = fopen(invalid_maps[i], "r");
		graph_t *graph = graph_create(valid_chars);
		graph->rows = 8;
		graph->cols = 23;
		matrix_graph_create(fp, graph);
		matrix_enrich(graph);
		ck_assert_int_eq(matrix_validate_maze(graph), 0);
	}
} END_TEST START_TEST(test_dijkstra_search_valid)
{
	FILE *fp = fopen("./test/test_data/valid_map.txt", "r");
	graph_t *graph = graph_create(valid_chars);
	get_set_graph_size(fp, graph);
	matrix_graph_create(fp, graph);
	matrix_enrich(graph);
	ck_assert_int_eq(dijkstra_search(graph), 1);

}

END_TEST START_TEST(test_dijkstra_search_invalid)
{
	FILE *fp = fopen("./test/test_data/valid_map_no_path.txt", "r");
	graph_t *graph = graph_create(valid_chars);
	get_set_graph_size(fp, graph);
	matrix_graph_create(fp, graph);
	matrix_enrich(graph);
	ck_assert_int_eq(dijkstra_search(graph), 0);
}

END_TEST static TFun core_tests[] = {
	test_graph_create,
	test_get_set_graph_size,
	test_get_set_graph_size_invalid,
	test_matrix_graph_create,
	test_matrix_graph_create_invalid,
	test_matrix_enrich,
	test_matrix_validate_maze_invalid,
	test_dijkstra_search_valid,
	test_dijkstra_search_invalid,
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
