#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>

#include "../include/io_helper.h"
#include "../include/matrix.h"

// TODO: For entire project
// [ ] Document and code comments
// [ ] Add ABC's to all library functions
// [ ] Implement optarg, no need for long opts
// [ ] Re-write tests for new graph_t struct design
// [ ] Write tests for pqueue library
// [ ] Handle memory leak issues
// [ ] create a directory of multiple map .txt files to run against the project

int main(int argc, char *argv[])
{
	int exit_status = 1;
	if (1 == argc) {
		fprintf(stderr, "maze: missing file argument\n");
		goto EXIT;
	}

	FILE *fp = fopen(argv[1], "r");
	if (!fp) {
		perror("maze");
		errno = 0;
		goto EXIT;

	}

	if (!validate_file(fp)) {
		fprintf(stderr, "maze: invalid file argument\n");
		goto FILE_EXIT;
	}

        char valid_chars[7] = { 0 };
        memcpy(valid_chars, "@ >", 3);
	int opt;
	// NOTE: getopt return values:
	//  -1: All options have been parsed
	//  '?': Option not in the optstring (invalid)
	//  ':': Option is missing argument
	while ((opt = getopt(argc, argv, "dDw")) != -1) {
		switch (opt) {
		case 'd':
                        strcat(valid_chars, "+");
			break;
		case 'D':
                        strcat(valid_chars, "#");
			break;
		case 'w':
                        strcat(valid_chars, "~");
			break;
		case '?':
			goto FILE_EXIT;
			break;
		default:
			break;
		}
	}


	// HACK: Does each function need to validate against NULL since it has already
	//  been validated in create and validate_file?
	graph_t *graph = graph_create(valid_chars);
	if (!graph) {
		fprintf(stderr, "graph_create: Error allocating memory\n");
		goto FILE_EXIT;
	}

	// Should break here with invalid_char.txt
	// Breaking here is not considered a valid file.
	if (!get_set_graph_size(fp, graph)) {
		goto GRAPH_EXIT;
	}

	// Breaking here is not considered a valid file either.
	if (!matrix_graph_create(fp, graph)) {
		printf("broke on create\n");
		goto GRAPH_EXIT;
	}

	if (!matrix_enrich(graph)) {
		printf("broke on enrich");
		goto GRAPH_EXIT;
	}

	// Breaking here is not considered a valid file.
	if (!matrix_validate_maze(graph)) {
		printf("Not a valid maze validate\n");
		goto GRAPH_EXIT;
	}

	dijkstra_search(graph);
        exit_status = 0;
	print_solved(graph);
	// print_solved(graph);
GRAPH_EXIT:
	matrix_destroy(graph);
FILE_EXIT:
	fclose(fp);
EXIT:
	return exit_status;
}
