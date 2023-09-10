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
 * @brief Struct that defines pointer to head node, pthread lock,
 *        and del_f that knows how to delete void*
 */
typedef struct llist_t llist_t;

/**
 * @brief Allocates linked-list
 * 
 * @return llist_t* On success, NULL on failure 
 */
llist_t *llist_create();

/**
 * @brief Function to delete linked list and free memory
 * 
 * @param p_llist Linked-list to delete
 */
// void llist_delete(llist_t **p_llist);

/**
 * @brief Adds void* to linked-list as a queue
 * 
 * @param llist Linked-list to enqueue() to
 * @param data custom_thing to be added
 * @return true On success
 * @return false On failure
 */
bool llist_enqueue(llist_t * llist, void *data);

/**
 * @brief Removes void* from linked-list as a queue
 * 
 * @param llist Linked-list to dequeue() from
 * @param data custom_thing** pointer of place to store data pointer to
 * @return true On success
 * @return false On failure
 */
void *llist_dequeue(llist_t * llist);

/**
 * @brief Adds void* to linked-list as a stack
 * 
 * @param llist Linked-list to push() to
 * @param data custom_struct to be added to linked-list
 * @return true On success
 * @return false On failure
 */
bool llist_push(llist_t * llist, void *data);

/**
 * @brief Removes void* from linked-list as a stack
 * 
 * @param llist Linked-list to pop() from
 * @param data custom_struct** pointer of place to store data pointer to
 * @return true On success
 * @return false On failure
 */
// bool llist_pop(llist_t *llist, vertex_t **data);

/**
 * @brief Checks if linked-list is empty
 * 
 * @param list Linked-list to check
 * @return true Is empty
 * @return false Not empty
 */
bool llist_is_empty(llist_t * llist);

// Emptys linked list without doing anything to stored pointers
//
void llist_destroy(llist_t * llist);

// uint64_t llist_get_size(llist_t *llist);

// vertex_t *llist_find(llist_t *llist, const char *id);

// void llist_print(llist_t *llist, int depth);

// llist_t *llist_duplicate(llist_t *llist);

#endif				/* LLIST_H */

/*** end of file ***/
