#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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


int main(void)
{
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
	// while (!feof(fp)) {
	//         char *curr_line = calloc(23, sizeof(char));
	//         fgets(curr_line, 23, fp);
	//         printf("%s", curr_line);
	// }

	// rewind(fp);
	if (!matrix_graph_create(fp, graph)) {
                printf("broke on create\n");
		return 1;
	}
	if (!matrix_enrich(graph)) {
                printf("broke on enrich");
		return 1;
	}
	print_graph(graph);
	// print_graph(graph);
	
        if (!matrix_validate_maze(graph)) {
                printf("Not a valid maze validate\n");
                return 1;
        }

        // if (!bfs(graph)) {
        //         printf("Broken in bfs");
        //         return 1;
        // }
	print_solved(graph);

	fclose(fp);

}
