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
		goto EXIT;
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
			goto EXIT;
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
		goto EXIT;
	}

	if (!get_set_graph_size(fp, graph)) {
		return 1;
	}

	if (!matrix_graph_create(fp, graph)) {
		printf("broke on create\n");
		return 1;
	}

	if (!matrix_enrich(graph)) {
		printf("broke on enrich");
		return 1;
	}

	if (!matrix_validate_maze(graph)) {
		printf("Not a valid maze validate\n");
		return 1;
	}

	if (!dijkstra_search(graph)) {
                print_graph(graph);
		printf("Broken in bfs");
		return 1;
	}

 GOOD_EXIT:
        print_graph(graph);
	print_solved(graph);
	matrix_destroy(graph);
 EXIT:
	fclose(fp);
	return exit_status;
}
