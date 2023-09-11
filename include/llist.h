/** @file llist.h
 * 
 * @brief linked-list library support queue/stack handling for void*
 *        Requires pthread library
 */
#ifndef LLIST_H
#define LLIST_H

#include <stdbool.h>
#include <stdint.h>
#include "../include/matrix.h"

/**
 * @brief Opaque data type for to interact with llist API.
 */
typedef struct llist_t llist_t;

/**
 * @brief Creates an empty list.
 * 
 * @return llist_t* Pointer to link list or NULL on failure
 */
llist_t *llist_create();

/**
 * @brief Puts heap allocated data at back of queue.
 * 
 * @param llist Pointer to the list to store the data.
 * @param data Void pointer to data to store in llist.
 * 
 * @return True on success, False on failure.
*/
bool llist_enqueue(llist_t * llist, void *data);

/**
 * @brief Extracts the oldest element from the queue.
 * 
 * @param llist Pointer to the list storing the data.
 * 
 * @return void* The oldest element in the queue or NULL on failure.
*/
void *llist_dequeue(llist_t * llist);

/**
 * @brief Puts heap allocated data at top of stack.
 * 
 * @param llist Pointer to the list to store the data.
 * @param data Void pointer to the data to store in llist.
 * 
 * @return True on success, False on failure.
*/
bool llist_push(llist_t * llist, void *data);

/**
 * @brief Checks if linked-list is empty
 * 
 * @param llist Linked-list to check
 * @return true Is empty
 * @return false Not empty
 */
bool llist_is_empty(llist_t * llist);

/**
 * @brief free() llist and nodes of llist.
 * 
 * @param llist linked-list to free. 
 */
void llist_destroy(llist_t * llist);

#endif
