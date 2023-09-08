#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

#include "../include/llist.h"

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
	uint16_t cols = 1;
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
	int exit_status = 0;
	graph->matrix = calloc(graph->rows, sizeof(vertex_t *));
	vertex_t **matrix = calloc(graph->rows, sizeof(*matrix));
	graph->start = NULL;
	graph->end = NULL;

	char letter = '\0';

	for (int row = 0; row < graph->rows; ++row) {
		char *curr_line = calloc(graph->cols + 2, sizeof(char));
		fgets(curr_line, graph->cols + 2, fp);
		char *tmp;
		if ((0 == row) || (row == (graph->rows - 1))) {
			for (int i = 0; i < strlen(curr_line); ++i) {
				if (' ' == curr_line[i]) {
					curr_line[i] = 26;
				}
			}
		}
		size_t delim = 0;
		delim = strcspn(curr_line, "#");
		for (size_t i = 0; i < delim; ++i) {
			curr_line[i] = 26;
		}
		char *rear_delim = strrchr(curr_line, '#');
		for (size_t i = strlen(curr_line) - 2;
		     i > ((strlen(curr_line) - strlen(rear_delim))); --i) {
			curr_line[i] = 26;
		}
		graph->matrix[row] = calloc(graph->cols, sizeof(vertex_t));

		for (int col = 0; col < strlen(curr_line) - 1; ++col) {
			letter = curr_line[col];
			switch (letter) {
			case '@':
				if (graph->start) {
					goto EXIT;
				}
				graph->start = graph->matrix[row] + col;
				graph->start->level = INT_MAX;
				graph->start->value = START;
				graph->start->parent = graph->start;
				break;
			case '>':
				if (graph->end) {
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
			case '\n':
				break;
			default:
				break;
			}
			graph->matrix[row][col].letter = letter;
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
	for (int row = 0; row < graph->rows; ++row) {
		for (int col = 0; col < graph->cols; ++col) {
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

	for (int row = 0; row < graph->rows; ++row) {
		for (int col = 0; col < graph->cols; ++col) {
			current = &(graph->matrix[row][col]);
			if (current->letter == ' ' || current->letter == '>'
			    || current->letter == '@') {
				for (int i = 0; i < 4; ++i) {
					int tgt_x = row + neighbor_x[i];
					int tgt_y = col + neighbor_y[i];

					if ((tgt_x > -1)
					    && (tgt_x < graph->rows)
					    && (tgt_y > -1)
					    && (tgt_y < graph->cols)) {
						neighbor =
						    &(graph->
						      matrix[tgt_x][tgt_y]);
						if ((neighbor->letter == 26)
						    || (neighbor->letter ==
							'\n')) {
							printf
							    ("Invalid maze\n");
							printf
							    ("Broken on %d:%d\n",
							     row, col);
							return 0;
						}
						if (neighbor->value != WALL) {
							matrix_add_edge(current,
									neighbor);
						}
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
	llist_t *queue = llist_create();
	llist_enqueue(queue, graph->start);
	uint16_t level = 0;

	while (!llist_is_empty(queue)) {
		vertex_t *node = (vertex_t *) llist_dequeue(queue);
		edge_t *current = node->neighbors;
		if (!current) {
			return;
		}
		do {
			if (!current->destination->level) {
				current->destination->level = level + 1;
				current->destination->parent = node;
				llist_enqueue(queue, current->destination);
			}
			current = current->next;
		} while (current);
		level += 1;
	}

	llist_t *stack = llist_create();
	vertex_t *node = graph->end;
	int counter = 0;
	while (node != node->parent) {
		node->letter = '.';
		llist_push(stack, node);
                if (!node->parent) {
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
	for (int i = 0; i < graph->rows; ++i) {
		for (int j = 0; j < graph->cols; ++j) {
			if (graph->matrix[i][j].letter == '.') {
				printf("\033[1;31m%c\033[0m",
				       graph->matrix[i][j].letter);
			} else {
				printf("%c", graph->matrix[i][j].letter);
			}
		}
		printf("\n");
	}
}
