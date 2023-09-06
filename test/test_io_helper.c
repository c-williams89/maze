#include <check.h>
#include <stdio.h>

#include "../include/io_helper.h"

START_TEST(test_validate_file_valid) {
        FILE *fp = fopen("./data/valid_map.txt", "r");
        ck_assert_int_eq(validate_file(fp), 1);
} END_TEST

START_TEST(test_validate_file_invalid) {
        const char *invalid_files[] = {
                "/dev/null",
                "/dev/urandom",
                "/dev/zero"
        };

        for (int i = 0; i < 3; ++i) {
                FILE *fp = fopen(invalid_files[i], "r");
                ck_assert_int_eq(validate_file(fp), 0);
        }

        FILE *invalid_streams[] = {
                stdin,
                stdout,
                stderr
        };

        for (int i = 0; i < 3; ++i) {
                ck_assert_int_eq(validate_file(invalid_streams[i]), 0);

        }

} END_TEST

START_TEST(test_get_graph_size_pass) {
        FILE *fp = fopen("./data/valid_map.txt", "r");
        graph_data *graph = get_graph_size(fp);
        ck_assert_ptr_ne(graph, NULL);
        ck_assert_int_eq(graph->rows, 8);
        ck_assert_int_eq(graph->cols, 23);
} END_TEST



static TFun core_tests[] = {
        test_validate_file_valid,
        test_validate_file_invalid,
        test_get_graph_size_pass,
        NULL
};

Suite *test_io_helper(void) {
        Suite *s = suite_create("test_io_helper");
        TFun *curr = NULL;
        TCase *tc_core = tcase_create("core");

        curr = core_tests;
        while (*curr) {
                tcase_add_test(tc_core, *curr++);
        }
        suite_add_tcase(s, tc_core);
        return s;
}