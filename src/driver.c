#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../include/io_helper.h"
#include "../include/matrix.h"

int main (void) {
        FILE *fp = fopen("./data/valid_map.txt", "r");
        if (!fp) {
                perror("Oh no");
                errno = 0;
                return 1;
        }

        if (!validate_file(fp)) {
                printf("did it again\n");
                return 1;
        }

        graph_t *graph = graph_create();
        if (!get_set_graph_size(fp, graph)) {
                return 1;
        }
        matrix_graph_create(fp, graph);
        print_graph(graph);
        graph = matrix_enrich(graph);
        print_graph(graph);
        bfs(graph);
        print_solved(graph);

}