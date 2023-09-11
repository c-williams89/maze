#include <stdlib.h>
#include <errno.h>

#include "../include/llist.h"
#include "../include/matrix.h"

struct node_t {
	struct node_t *next;
	void *data;		//*data is of type vertex_t
};

struct llist_t {
	struct node_t *head;
	struct node_t *tail;
	uint64_t sz;
};

llist_t *llist_create()
{
	llist_t *llist = calloc(1, sizeof(*llist));
	if (!llist) {
		perror("llist_create");
		errno = 0;
	}
	return llist;
}

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

void *llist_dequeue(llist_t * list)
{
	if (!list || !list->head) {
		return NULL;
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

bool llist_is_empty(llist_t * llist)
{
	if (!llist) {
		return false;
	}
	return llist->sz > 0 ? false : true;
}

void llist_destroy(llist_t * llist)
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
	free(llist);
}
