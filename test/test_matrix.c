#include <check.h>
#include <stdio.h>
#include <limits.h>

#include "../include/matrix.h"

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

START_TEST (test_matrix_create_valid) {
        FILE *fp = fopen("./data/valid_map.txt", "r");
        vertex_t **matrix = matrix_create(fp, 83, 23);
        // ck_assert_int_eq((matrix[1] + 11)->level, INT_MAX);
        ck_assert_ptr_ne(matrix, NULL);
} END_TEST

static TFun core_tests[] = {
        test_matrix_create_valid,
        NULL
};

Suite *test_matrix(void) {
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