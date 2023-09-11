#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>

#include "../include/io_helper.h"
#include "../include/matrix.h"

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

	graph_t *graph = graph_create(valid_chars);
	if (!graph) {
		fprintf(stderr, "graph_create: Error allocating memory\n");
		goto FILE_EXIT;
	}

	if (!get_set_graph_size(fp, graph)) {
		printf("Broke here");
		goto GRAPH_EXIT;
	}

	if (!matrix_graph_create(fp, graph)) {
		goto GRAPH_EXIT;
	}

	if (!matrix_enrich(graph)) {
		goto GRAPH_EXIT;
	}

	if (!matrix_validate_maze(graph)) {
		goto GRAPH_EXIT;
	}

	dijkstra_search(graph);
	exit_status = 0;
	print_solved(graph);
 GRAPH_EXIT:
	matrix_destroy(graph);
 FILE_EXIT:
	fclose(fp);
 EXIT:
	return exit_status;
}
