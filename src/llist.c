#include <stdlib.h>

#include "../include/llist.h"
#include "../include/matrix.h"
// typef struct vertex_t vertex_t;
struct node_t {
	struct node_t *next;
	void *data;		//*data is of type vertex_t
};

struct llist_t {
	struct node_t *head;
	struct node_t *tail;
	uint64_t sz;
};
/*

// Deletes all nodes
//
static void llist_delete_nodes(llist_t * llist);
*/

llist_t *llist_create()
{
	llist_t *llist = calloc(1, sizeof(*llist));

	return llist;
}

/*
// void llist_delete(llist_t ** p_llist)
// {
// 	if (!p_llist) {
// 		return;
// 	}

// 	llist_delete_nodes(*p_llist);

// 	(*p_llist)->head = NULL;
// 	(*p_llist)->tail = NULL;
// 	free(*p_llist);
// 	*p_llist = NULL;
// }				llist_delete()

// static void llist_delete_nodes(llist_t * llist)
// {
// 	struct node_t *node = llist->head;
// 	struct node_t *temp = NULL;

// 	while (node) {
// 		temp = node;
// 		node = node->next;

// 		destroy_vertex(temp->data);
// 		--llist->sz;
// 		temp->data = NULL;
// 		temp->next = NULL;
// 		free(temp);
// 		temp = NULL;
// 	}
// }			
*/

bool llist_enqueue(llist_t * llist, void *data)
{
	if (!llist || !data) {
		return false;
	}

	struct node_t *node = malloc(sizeof(*node));
	if (!node) {
		return false;
	}

	node->data = data;
	node->next = NULL;

	if (llist->tail) {
		llist->tail->next = node;
	} else {
		llist->head = node;
	}

	llist->tail = node;
	++llist->sz;

	return true;
}

/*
// bool llist_dequeue(llist_t * llist, vertex ** data)
// {
// 	bool ret = false;
// 	if (!data) {
// 		goto DEQUEUE;
// 	}
// 	// set to NULL in case of failure after verifying we can set to NULL
// 	*data = NULL;
// 	if (!llist) {
// 		goto DEQUEUE;
// 	}

// 	if (!llist->head) {
// 		goto DEQUEUE;
// 	}

// 	struct node_t *temp = llist->head;
// 	llist->head = temp->next;
// 	*data = temp->data;

// 	if (!llist->head) {
// 		llist->tail = NULL;
// 	}

// 	temp->next = NULL;
// 	temp->data = NULL;
// 	free(temp);
// 	temp = NULL;
// 	ret = true;
// 	--llist->sz;

//  DEQUEUE:
// 	return ret;
// }				llist_dequeue()

*/
void *llist_dequeue(llist_t * list)
{
	if (!list || !list->head) {
		return 0;
	}
	void *data = list->head->data;
	struct node_t *tmp = list->head;
	list->head = list->head->next;
	free(tmp);

	if (!list->head) {
		list->tail = list->head;
	}
	--list->sz;
	return data;
}

bool llist_push(llist_t * llist, void *data)
{
	if (!llist || !data) {
		return false;
	}

	struct node_t *node = malloc(sizeof(*node));
	if (!node) {
		return false;
	}
	node->data = data;

	node->next = llist->head;
	llist->head = node;
	++llist->sz;

	return true;
}

/*

// inline bool llist_pop(llist_t * llist, vertex ** data)
// {
// 	return llist_dequeue(llist, data);
// }				llist_pop()

*/
bool llist_is_empty(llist_t * llist)
{
	if (!llist) {
		return false;
	}
	return llist->sz > 0 ? false : true;
}

/*				llist_is_empty()
uint64_t llist_get_size(llist_t * llist)
{
	if (!llist) {
		return 0;
	}
	return llist->sz;
}				llist_get_size() 

void llist_purge(llist_t * llist)
{
	if (!llist) {
		return;
	}

	struct node_t *node = llist->head;
	struct node_t *temp = NULL;
	while (node) {
		temp = node;
		node = node->next;
		free(temp);
	}
	llist->head = NULL;
	llist->tail = NULL;
}				llist_purge()

// vertex_t *llist_find(llist_t * llist, const char *id)
// {
// 	vertex_t *data = NULL;
// 	struct node_t *node = llist->head;
// 	while (node) {
// 		if (is_match(node->data, id)) {
// 			data = node->data;
// 			break;
// 		}
// 		node = node->next;
// 	}
// 	return data;
// }

// void llist_print(llist_t * llist, int depth)
// {
// 	if (!llist) {
// 		return;
// 	}

// 	struct node_t *node = llist->head;
// 	while (node) {
// 		print_vertex(node->data, depth);
// 		node = node->next;
// 	}
// }

llist_t *llist_duplicate(llist_t * llist)
{
	llist_t *copy = llist_create();
	if (!copy) {
		return NULL;
	}

	struct node_t *node = llist->head;
	while (node) {
		llist_enqueue(copy, node->data);
		node = node->next;
	}
	return copy;
}

*/
