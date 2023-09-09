#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

#include "../include/llist.h"
#include "../include/p_queue.h"

enum { SPACE = 1, WALL = 11, WATER = 3, END = 1, START = 0, DOOR = 3 };

typedef struct vertex_t {
	struct vertex_t *parent;
	struct edge_t *neighbors;
	int value;
	char letter;
	int level;
	int num_children;
} vertex_t;

typedef struct edge_t {
	vertex_t *destination;
	struct edge_t *next;
} edge_t;

typedef struct graph_t {
	vertex_t **matrix;
	vertex_t *start;
	vertex_t *end;
	uint16_t rows;
	uint16_t cols;
        uint16_t size;
} graph_t;

static void matrix_add_edge(vertex_t * current, vertex_t * neighbor);

graph_t *graph_create(void)
{
	graph_t *graph = calloc(1, sizeof(*graph));
	return graph;
}

int get_set_graph_size(FILE * fp, graph_t * graph)
{
	int exit_status = 0;
	if (!graph) {
		perror("get_graph_size: Error allocating memory\n");
		errno = 0;
		goto EXIT;
	}
	const char *valid_chars = "@ >#+~";
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
		if (!strchr(valid_chars, c)) {
			goto EXIT;
		}
		++cols;
	}
	rewind(fp);
	exit_status = 1;
 EXIT:
	return exit_status;
}

int matrix_graph_create(FILE * fp, graph_t * graph)
{
        printf("Rows: %d, cols: %d\n", graph->rows, graph->cols);
	int exit_status = 0;
	graph->matrix = calloc(graph->rows + 2, sizeof(vertex_t *));
	vertex_t **matrix = calloc(graph->rows + 2, sizeof(*matrix));
        // for (int col = 0; col < graph->cols)
	graph->start = NULL;
	graph->end = NULL;
        char letter = '\0';
        
        for (int row = 0; row < graph->rows + 2; ++row) {
                graph->matrix[row] = calloc(graph->cols + 2, sizeof(vertex_t));
                if (!graph->matrix[row]) {
                        printf("This failed\n");
                }
                graph->matrix[row][0].letter = 'a';
                graph->matrix[row][graph->cols + 1].letter = 'a';

                if ((0 == row) || (row == (graph->rows + 1))) {
                        for (int col = 0; col < graph->cols + 1; ++col) {
                                graph->matrix[row][col].letter = 'a';
                                graph->matrix[row][col].value = INT_MIN;
                        }
                } else {
                        for (int col = 1; col < graph->cols + 2; ++col) {
                                letter = fgetc(fp);
                                if (letter == '\n' || letter == EOF) {
                                        break;
                                }
                                switch (letter)
                                {
                                case '@':
				        if (graph->start) {
				        	goto EXIT;
				        }
				        graph->start = graph->matrix[row] + col;
				        graph->start->level = INT_MAX;
				        graph->start->value = START;
				        graph->start->parent = graph->start;
                                        graph->size += 1;
				        break;
			        case '>':
			        	if (graph->end) {
			        		goto EXIT;
			        	}
                                        graph->size += 1;

			        	graph->end = graph->matrix[row] + col;
			        	graph->end->value = END;
			        	break;
			        case '#':
                                        graph->size += 1;

			        	graph->matrix[row][col].value = WALL;
			        	break;
			        case ' ':
                                        graph->size += 1;
			        	graph->matrix[row][col].value = DOOR;
			        	break;
			        // case '\n':
                                //         continue;
			        	// break;
                                }
                                graph->matrix[row][col].letter = letter;
                        }
                }
        }
        if (!graph->start || !graph->end) {
                goto EXIT;
        }
	exit_status = 1;
 EXIT:
	return exit_status;
}

void print_graph(graph_t * graph)
{
	for (int row = 1; row < graph->rows + 1; ++row) {
		for (int col = 1; col < graph->cols + 1; ++col) {
			printf("%c", graph->matrix[row][col].letter);
		}
		printf("\n");
	}
        printf("\n\n");
        for (int row = 0; row < graph->rows + 2; ++row) {
                for (int col = 0; col < graph->cols + 2; ++col) {
			printf("%c", graph->matrix[row][col].letter);
                }
                printf("\n");
        }
}

int matrix_enrich(graph_t * graph)
{
	vertex_t *current = NULL;
	vertex_t *neighbor = NULL;

	int neighbor_x[] = { -1, 0, 1, 0 };
	int neighbor_y[] = { 0, 1, 0, -1 };

	for (int row = 0; row < graph->rows + 2; ++row) {
		for (int col = 0; col < graph->cols + 2; ++col) {
			current = &(graph->matrix[row][col]);
                        // if (curr)
			if (current->letter == ' ' || current->letter == '>'
			    || current->letter == '@' || current->letter == 'a' || current->letter == '#') {
				for (int i = 0; i < 4; ++i) {
					int tgt_x = row + neighbor_x[i];
					int tgt_y = col + neighbor_y[i];

					if ((tgt_x > -1)
					    && (tgt_x < graph->rows + 2)
					    && (tgt_y > -1)
					    && (tgt_y < graph->cols + 2)) {
						neighbor =
						    &(graph->
						      matrix[tgt_x][tgt_y]);
						// if ((neighbor->letter == 26)
						//     || (neighbor->letter ==
						// 	'\n')) {
						// 	printf
						// 	    ("Invalid maze\n");
						// 	printf
						// 	    ("Broken on %d:%d\n",
						// 	     row, col);
						// 	return 0;
						// }
						// if (neighbor->value != WALL) {
                                                        // printf("Adding: %c\n", current->letter);
							matrix_add_edge(current,
									neighbor);
						// }
						current->num_children += 1;
					}

				}
			}
		}
	}
	return 1;
}

static void matrix_add_edge(vertex_t * current, vertex_t * neighbor)
{
	edge_t *new_edge = calloc(1, sizeof(*new_edge));

	new_edge->destination = neighbor;
	new_edge->next = current->neighbors;
	current->neighbors = new_edge;
}

int bfs(graph_t * graph)
{
        // TODO: Come back to this after confirming new validation works
        /*
        pqueue_t *pqueue = pqueue_create(graph->size);
        pqueue_insert(pqueue, graph->start->value, graph->start);
        uint16_t level = 0;
        printf("Graph size: %d\n", graph->size);
        while (!pqueue_is_empty(pqueue)) {
                vertex_t *node = (vertex_t *)pqueue_pull(pqueue);
                edge_t *current = node->neighbors;
                if (!current) {
                        return;
                }

                do {
                        if (!current->destination->level) {
                                current->destination->level = level + 1;
                                current->destination->parent = node;
                                pqueue_insert(pqueue, current->destination->value, current->destination);
                        }
                        current = current->next;
                } while (current);

                level += 1;
        }
        */

        // NOTE: Everything below works
        
	llist_t *queue = llist_create();
	llist_enqueue(queue, graph->start);
	uint16_t level = 0;

	while (!llist_is_empty(queue)) {
		vertex_t *node = (vertex_t *) llist_dequeue(queue);
		edge_t *current = node->neighbors;
		if (!current) {
                        break;
			// return;
		}
		do {
			if (!current->destination->level && current->destination->letter != 'a') {
				current->destination->level = level + 1;
				current->destination->parent = node;
				llist_enqueue(queue, current->destination);
			}
			current = current->next;
		} while (current);
		level += 1;
	}

        // When here, graph.end.parent = NULL;
	llist_t *stack = llist_create();
	vertex_t *node = graph->end;
	int counter = 0;
        // BUG: infinte loop here
	while (node != node->parent) {
                printf("Inside while\n");
		node->letter = '.';
		llist_push(stack, node);
                if (!node->parent) {
                        printf("returning from list\n");
                        return 0;
                }
		node = node->parent;
		++counter;
	}
	graph->end->letter = '>';
        return 1;
}
// TODO: Possibly put validation in it's own function so that we can still print original maze

void print_solved(graph_t * graph)
{
        for (int row = 1; row < graph->rows + 1; ++row) {
		for (int col = 1; col < graph->cols + 1; ++col) {
			printf("%c", graph->matrix[row][col].letter);
		}
		printf("\n");
	}
}

// start is reset here, consider returning the llist
bool matrix_validate_maze(graph_t *graph) {
        llist_t *queue = llist_create();
        vertex_t *node = &(graph)->matrix[0][0];
        llist_enqueue(queue, node);
        uint16_t level = 0;
        
        while (!llist_is_empty(queue)) {
                vertex_t *next = (vertex_t *)llist_dequeue(queue);
                if (next->letter == '@' || next->letter == '>') {
                        return false;
                }

                edge_t *current = next->neighbors;
                if (!current) {
                        // BUG: Breaks on the return false which is needed to ensure the
                        //  while loop isnt entered with a null pointer.
                        break;
                }

                while (current) {
                        if (current->destination->letter == '@' || current->destination->letter == '>') {
                                return false;
                        }

                        if (!current->destination->level && current->destination->letter != '#') {
                                current->destination->level = level + 1;
                                current->destination->parent = next;
                                current->destination->letter = '!';
                                llist_enqueue(queue, current->destination);
                        }
                        current = current->next;
                }
                level += 1;
        }
        return true;
}