#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>

#include "../include/io_helper.h"
#include "../include/matrix.h"

typedef struct opt_t {
	bool b_wall;
	bool b_water;
	bool b_door;
        // Based on command line args, strncat to valid_chars '+' or '~' to compare against;
        // When validating character within matrix_enrich, strrchr against this string
        // to determine whether it is a valid neighbor or not.
        char *valid_chars;
        
} opt_t;

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

	opt_t *arg_flags = calloc(1, sizeof(*arg_flags));
	if (!arg_flags) {
		fprintf(stderr, "maze: Unable to allocate memory\n");
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
			arg_flags->b_door = true;
			break;
		case 'D':
                        strcat(valid_chars, "#");
			arg_flags->b_wall = true;
			break;
		case 'w':
                        strcat(valid_chars, "~");
			arg_flags->b_water = true;
			break;
		case '?':
			free(arg_flags);
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
	// NOTE: Need to pass args struct to bfs
	if (!bfs(graph)) {
		printf("Broken in bfs");
		return 1;
	}
	// print_solved(graph);
 GOOD_EXIT:
	print_solved(graph);
	free(arg_flags);
	matrix_destroy(graph);
 EXIT:
	fclose(fp);
	return exit_status;
}
