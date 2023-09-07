#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <limits.h>

typedef struct graph_data {
        uint16_t rows;
        uint16_t cols;
} graph_data;

int validate_file(FILE *fp) {
        struct stat path_stat;
        int exit_status = 0;
        int fileno(FILE *fp);
        int fd = fileno(fp);  

        // Tests that fstat does not fail
        if (-1 == fstat(fd, &path_stat)) {
                perror("validate_file: Unable to retrieve file information");
                errno = 0;
                goto EXIT;
        }

        // Tests the case where stdin, stdout, or stderr have been passed.
        if (3 > fd) {
                fprintf(stderr, "validate_file: Invalid stream. Must be file.\n");
                goto EXIT;
        }

        if (S_ISREG(path_stat.st_mode)) {
                if (0 < path_stat.st_size) {
                        exit_status = 1;
                }
        }    

EXIT:
        return exit_status;
}

// TODO: Build a struct for map information, rows, columns, start, and end to pass that 
//  struct around where needed
// NOTE: Consider moving to the matrix helper source
graph_data * get_graph_size(FILE *fp) {
        graph_data *graph = calloc(1, sizeof(*graph));
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
        // printf("Rows: %d\tCols: %d\n", graph->rows, graph->cols);
EXIT:
        return graph;
}
