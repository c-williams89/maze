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
        opt_t *arg_flags =  calloc(1, sizeof(*arg_flags));
        
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
                fclose(fp);
                goto EXIT;
        }
        
        int opt;
        // NOTE: getopt return values:
        //  -1: All options have been parsed
        //  '?': Option not in the optstring (invalid)
        //  ':': Option is missing argument
        while ((opt = getopt(argc, argv, "dDw")) != -1) {
                switch (opt)
                {
                case 'd':
                        arg_flags->b_door = true;
                        break;
                case 'D':
                        arg_flags->b_wall = true;
                        break;
                case 'w':
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
	
        graph_t *graph = graph_create();
	if (!get_set_graph_size(fp, graph)) {
		return 1;
	}

	if (!matrix_graph_create(fp, graph)) {
                printf("broke on create\n");
		return 1;
	}
        
        // NOTE: Need to pass args struct to enrich
	if (!matrix_enrich(graph)) {
                printf("broke on enrich");
		return 1;
	}
	// print_graph(graph);
	// print_graph(graph);
	
        if (!matrix_validate_maze(graph)) {
                printf("Not a valid maze validate\n");
                return 1;
        }

        if (!bfs(graph)) {
                printf("Broken in bfs");
                return 1;
        }
	print_solved(graph);

	// fclose(fp);
EXIT:
        // fclose(fp);
        return exit_status;
}
