#ifndef P_QUEUE_H
#define P_QUEUE_H
#include <stdbool.h>
	typedef struct pqueue_t pqueue_t;


	pqueue_t *pqueue_create(int capacity);
	// Returns true if there are no elements in the priority queue
	bool pqueue_is_empty(pqueue_t *pqueue);

	// Inserts item into priority queue based on ordering of key
	bool pqueue_insert(pqueue_t *pqueue, int key, int data);
	

	// Removes lowest priority element from queue and returns it
	int pqueue_pull(pqueue_t *pqueue);

	// Returns, but does not remove the lowest priority element in the queue
	int pqueue_peek(pqueue_t *pqueue);

	void pqueue_destroy(pqueue_t **pqueue);

	void pq_print(pqueue_t *pq);
#endif