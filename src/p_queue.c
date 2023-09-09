#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>

#include "../include/p_queue.h"

typedef struct node_t {
        // int data;
        void * data;
        int priority;
        int level;

} node_t;

struct pqueue_t {
        struct node_t *back;
        struct node_t *heap;
        uint32_t count;
        uint32_t capacity;
};

// TODO: Write custom function to compare value within vertex_t struct

static void heapify_up(uint32_t position, node_t *heap);
static void heapify_down(uint32_t position, uint64_t size, node_t *heap);

pqueue_t *pqueue_create(int capacity) {
        pqueue_t *pq = NULL;
        if (capacity < 1) {
                fprintf(stderr, "pqueue_create: Invalid argument. Size must be integer greater than 0.\n");
                goto CREATE_EXIT;
        }

        pq = calloc(1, sizeof(pqueue_t));
        if (!pq) {
                perror("pqueueu_create: Unable to allocate memory for priority queue\n");
                errno = 0;
                goto CREATE_EXIT;
        }

        pq->heap = calloc(capacity, sizeof(node_t));
        if (!pq->heap) {
                perror("pqueue_create: Unable to allocate memory for target capacity\n");
                errno = 0;
                free(pq);
                pq = NULL;
                goto CREATE_EXIT;
        }

        pq->count = 0;
        pq->back = pq->heap;
        pq->capacity = capacity;
CREATE_EXIT:
        return pq;
}

bool pqueue_insert(pqueue_t *pqueue, int key, void * data) {
        
        bool return_status = false;
        if (!pqueue) {
                fprintf(stderr, "pqueue_insert: Invalid argument - NULL\n");
                goto INSERT_EXIT;
        }

        if (pqueue->count == pqueue->capacity) {
                fprintf(stderr, "pqueue insert: Queue full\n");
                goto INSERT_EXIT;
        }

        return_status = true;
        pqueue->heap[pqueue->count].data = data;
        pqueue->heap[pqueue->count].priority = key;
        pqueue->heap[pqueue->count].level = 0;
        heapify_up(pqueue->count, pqueue->heap);

        pqueue->back++;
        pqueue->count++;

INSERT_EXIT:
        return return_status;
}

static void heapify_up(uint32_t position, node_t *heap) {
        if (0 == position) {
                heap[position] = heap[0];
                return;
        }
        uint32_t parent = (position - 1) / 2;
        // if (parent < 0) {
        //         return;
        // }
        node_t tmp;
        if (heap[parent].priority > heap[position].priority) {
                tmp = heap[parent];
                heap[parent] = heap[position];
                heap[position] = tmp;
                heapify_up(parent, heap);
        }
}

void * pqueue_pull(pqueue_t *pqueue) {
        
        if (!pqueue || !pqueue->heap) {
                fprintf(stderr, "pqueue_pull: Invalid argument - NULL\n");
                return NULL;
        }
        void * temp;
        if (!pqueue->count) {
                fprintf(stderr, "pqueue_pull: Queue is empty\n");
                return NULL;
        }

        temp = pqueue->heap[0].data;
        pqueue->count--;
        pqueue->back--;
        pqueue->heap[0] = pqueue->heap[pqueue->count];
        heapify_down(0, pqueue->count, pqueue->heap);
        return temp;
        
}

static void heapify_down(uint32_t position, uint64_t size, node_t *heap) {
        uint32_t l_child = (2 * position) + 1;
        uint32_t r_child = (2 * position) + 2;

        if (l_child >= size) {
                return;
        }

        uint32_t swap_idx = heap[l_child].priority < heap[r_child].priority ? l_child : r_child;

        if (heap[position].priority > heap[swap_idx].priority) {
                node_t tmp = heap[swap_idx];
                heap[swap_idx] = heap[position];
                heap[position] = tmp;
                heapify_down(swap_idx, size, heap);
        }
}

/* Function currently unused
void pq_print(pqueue_t *pq) {
        for (uint32_t i = 0; i < pq->count; ++i) {
                printf("%d: %d\n", i, pq->heap[i].data);
        }
}
*/

bool pqueue_is_empty(pqueue_t *pqueue) {
        return (0 == pqueue->count) ? true : false;
}
