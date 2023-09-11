#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

#include "../include/llist.h"
#include "../include/p_queue.h"

enum { SPACE = 1, WALL = 11, WATER = 3, END = 1, START = 0, DOOR = 2 };

typedef struct vertex_t {
	struct vertex_t *parent;
	struct edge_t *neighbors;
	int value;
	int weight;
	char letter;
	int level;
	bool path;
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
	char valid_chars[7];
} graph_t;

static void matrix_add_edge(vertex_t * current, vertex_t * neighbor);
static void matrix_enrich_border(graph_t * graph);

graph_t *graph_create(char *valid_chars)
{
	graph_t *graph = calloc(1, sizeof(*graph));
	if (!graph) {
		perror("graph_create");
		errno = 0;
		goto EXIT;
	}
	memcpy(graph->valid_chars, valid_chars, 6);
 EXIT:
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
	char valid[] = "@ >#~+";
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

		if (!strchr(valid, c)) {
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
	int exit_status = 0;
	//TODO: ABC here
	graph->matrix = calloc(graph->rows + 2, sizeof(vertex_t *));
	graph->start = NULL;
	graph->end = NULL;
	char letter = '\0';

	for (int row = 0; row < graph->rows + 2; ++row) {
		graph->matrix[row] = calloc(graph->cols + 2, sizeof(vertex_t));
		if (!graph->matrix[row]) {
			perror("matrix_graph_create");
			errno = 0;
			goto EXIT;
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
				switch (letter) {
				case '@':
					if (graph->start) {
						fprintf(stderr,
							"Invalid Map\n");
						goto EXIT;
					}

					graph->start = graph->matrix[row] + col;
					graph->start->level = INT_MAX;
					graph->start->value = START;
					graph->start->parent = graph->start;
					break;
				case '>':
					if (graph->end) {
						fprintf(stderr,
							"Invalid Map\n");
						goto EXIT;
					}

					graph->end = graph->matrix[row] + col;
					graph->end->value = END;
					break;
				case '#':
					graph->matrix[row][col].value = WALL;
					break;
				case ' ':
					graph->matrix[row][col].value = SPACE;
					break;
				case '+':
					graph->matrix[row][col].value = DOOR;
					break;
				case '~':
					graph->matrix[row][col].value = WATER;
					break;
				}
				graph->matrix[row][col].letter = letter;
				graph->size += 1;
			}
		}
	}
	if (!graph->start || !graph->end) {
		fprintf(stderr, "Invalid Map\n");
		goto EXIT;
	}
	exit_status = 1;
 EXIT:
	return exit_status;
}

int matrix_enrich(graph_t * graph)
{
	int count = 0;
	vertex_t *current = NULL;
	vertex_t *neighbor = NULL;

	int neighbor_x[] = { -1, 0, 1, 0 };
	int neighbor_y[] = { 0, 1, 0, -1 };

	for (int row = 0; row < graph->rows + 2; ++row) {
		for (int col = 0; col < graph->cols + 2; ++col) {
			current = &(graph->matrix[row][col]);
			if (strchr(graph->valid_chars, current->letter)) {
				for (int i = 0; i < 4; ++i) {
					int tgt_x = row + neighbor_x[i];
					int tgt_y = col + neighbor_y[i];

					if ((tgt_x > -1)
					    && (tgt_x < graph->rows + 2)
					    && (tgt_y > -1)
					    && (tgt_y < graph->cols + 2)) {
						neighbor =
						    &(graph->matrix[tgt_x]
						      [tgt_y]);
						if (strchr
						    (graph->valid_chars,
						     neighbor->letter)) {
							++count;
							matrix_add_edge(current,
									neighbor);
						}
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
	if (new_edge) {
		new_edge->destination = neighbor;
		new_edge->next = current->neighbors;
		current->neighbors = new_edge;
	}
}

int dijkstra_search(graph_t * graph)
{
	pqueue_t *pqueue = pqueue_create(graph->size);
	pqueue_insert(pqueue, graph->start->value, graph->start);
	uint16_t level = 0;
	while (!pqueue_is_empty(pqueue)) {
		vertex_t *node = (vertex_t *) pqueue_pull(pqueue);
		edge_t *current = node->neighbors;
		while (current) {
			if (!current->destination->level) {
				current->destination->weight =
				    node->weight + current->destination->value;
				current->destination->value += node->value;
				current->destination->level = level + 1;
				current->destination->parent = node;
				pqueue_insert(pqueue,
					      current->destination->weight,
					      current->destination);
			} else {
				int weight =
				    node->weight + current->destination->value;
				if (weight < current->destination->weight) {
					current->destination->parent = node;
					current->destination->weight = weight;
					pqueue_insert(pqueue,
						      current->
						      destination->weight,
						      current->destination);
				}
			}
			current = current->next;
		}
		level += 1;
	}

	pqueue_destroy(pqueue);
	llist_t *stack = llist_create();
	vertex_t *node = graph->end;
	int counter = 0;
	while (node != node->parent) {
		node->path = true;
		llist_push(stack, node);
		if (!node->parent) {
			llist_destroy(stack);
			return 0;
		}
		node = node->parent;
		++counter;
	}
	graph->end->letter = '>';
	llist_destroy(stack);
	return 1;
}

void print_solved(graph_t * graph)
{
	for (int row = 1; row < graph->rows + 1; ++row) {
		for (int col = 1; col < graph->cols + 1; ++col) {
			vertex_t *curr = &(graph->matrix[row][col]);
			if (curr->path) {
				if (curr->letter == '+') {
					curr->letter = '/';
				} else if (curr == graph->end) {
					curr->letter = '>';
				} else if (curr->letter == '!') {
					curr->letter = ' ';
				} else {
					curr->letter = '.';
				}
			}
			printf("%c", graph->matrix[row][col].letter);
		}
		printf("\n");
	}
}

bool matrix_validate_maze(graph_t * graph)
{
	matrix_enrich_border(graph);
	bool b_exit_status = false;
	llist_t *queue = llist_create();
	vertex_t *node = &(graph)->matrix[0][0];
	llist_enqueue(queue, node);
	uint16_t level = 0;

	while (!llist_is_empty(queue)) {
		vertex_t *next = (vertex_t *) llist_dequeue(queue);
		if (next->letter == '@' || next->letter == '>') {
			goto EXIT;
		}

		edge_t *current = next->neighbors;

		while (current) {
			if (current->destination->letter == '@'
			    || current->destination->letter == '>') {
				goto EXIT;
			}

			if (!current->destination->level
			    && current->destination->letter != '#') {
				current->destination->level = level + 1;
				current->destination->parent = next;
				llist_enqueue(queue, current->destination);
			}
			current = current->next;
		}
		level += 1;
	}
	b_exit_status = true;
 EXIT:
	llist_destroy(queue);
	return b_exit_status;
}

static void matrix_enrich_border(graph_t * graph)
{
	int count = 0;

	vertex_t *current = &(graph->matrix[0][0]);
	vertex_t *neighbor = NULL;

	int neighbor_x[] = { -1, 0, 1, 0 };
	int neighbor_y[] = { 0, 1, 0, -1 };

	for (int row = 0; row < graph->rows + 2; ++row) {
		for (int col = 0; col < graph->cols + 2; ++col) {
			current = &(graph->matrix[row][col]);
			if (current->letter != '#' && !current->neighbors) {
				for (int i = 0; i < 4; ++i) {
					int tgt_x = row + neighbor_x[i];
					int tgt_y = col + neighbor_y[i];
					if ((tgt_x > -1)
					    && (tgt_x < graph->rows + 2)
					    && (tgt_y > -1)
					    && (tgt_y < graph->cols + 2)) {
						neighbor =
						    &(graph->matrix[tgt_x]
						      [tgt_y]);
						if (neighbor->letter != '#') {
							++count;
							matrix_add_edge(current,
									neighbor);
						}
					}
				}
			}
		}
	}
}

void matrix_destroy(graph_t * graph)
{
	if (!graph) {
		return;
	}

	if (graph->matrix) {
		for (int row = 0; row < graph->rows + 2; ++row) {
			if (graph->matrix[row]) {
				for (int col = 0; col < graph->cols + 2; ++col) {
					edge_t *tmp =
					    graph->matrix[row][col].neighbors;
					while (tmp) {
						edge_t *next = tmp->next;
						free(tmp);
						tmp = next;
					}
				}
				free(graph->matrix[row]);
			}
		}
		free(graph->matrix);
	}
	free(graph);
}
