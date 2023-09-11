#ifndef P_QUEUE_H
#define P_QUEUE_H
#include <stdbool.h>

/**
 * @brief Opaque data type to interact with priority queue (pqueue).
 */
typedef struct pqueue_t pqueue_t;

/**
 * @brief Creates pqueue of specified size.
 * 
 * @param capacity Size of pqueue to create.
 * 
 * @return Pointer to pqueue on success, NULL on failure.
 */
pqueue_t *pqueue_create(int capacity);

/**
 * @brief Checks if pqueue is empty
 * 
 * @param pqueue pqueue to check
 * 
 * @return true if empty, else false
 */
bool pqueue_is_empty(pqueue_t * pqueue);

/**
 * @brief Inserts data into pqueue, sorting by key.
 * 
 * @param pqueue Pointer to pqueue to insert into.
 * @param key Value to sort data on.
 * @param data Void pointer to data to store in pqueue.
 * 
 * @return True on success, else false.
 */
bool pqueue_insert(pqueue_t * pqueue, int key, void *data);

/**
 * @brief Returns lowest priority element from pqueue
 * 
 * @param pqueue Pqueue to pull from.
 * 
 * @return Lowest priority item, or NULL on failure.
 */
void *pqueue_pull(pqueue_t * pqueue);

/**
 * @brief free() pqueue and nodes of pqueue.
 * 
 * @param pqueue Pointer to pqueue to free().
 */
void pqueue_destroy(pqueue_t * pqueue);

#endif
