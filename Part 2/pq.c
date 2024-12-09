/*
pq.c

Unsorted Array Implementation
Note:faster time efficency could be achieved by implementing min-heap

Implementations for helper functions for priority queue construction and
manipulation.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2022

Modified by Alice Kjar
*/

#include <stdlib.h>
#include <assert.h>

#define INITIALITEMS 32
#define FOUND 1
#define MISSING 0

/* Definition of priority queue */
struct pq {
	int count;
	int allocated;
	void **queue;
	double *priorities;
};

/* Creates a new, empty priority queue 
	NOTE: This function was written by Grady Fitzpatrick and provided in the skeletion code */
struct pq *newPQ() {
	struct pq *pq = (struct pq *) malloc(sizeof(struct pq));
	assert(pq);
	pq->count = 0;
	pq->allocated = 0;
	pq->queue = NULL;
	pq->priorities = NULL;
	return pq;
}

/* Adds new item to priority queue
	NOTE: This function was written by Grady Fitzpatrick and provided in the skeletion code */
void enqueue(struct pq *pq, void *item, double priority) {
	assert(pq);
	if((pq->count + 1) > pq->allocated) {
		if (pq->allocated == 0) {
			pq->allocated = INITIALITEMS;
		} else {
			pq->allocated *= 2;
		}
		pq->queue = (void **) realloc(pq->queue, pq->allocated * sizeof(void *));
		assert(pq->queue);
		pq->priorities = (double *) realloc(pq->priorities, pq->allocated *
			sizeof(double));
		assert(pq->priorities);
	}
	(pq->queue)[pq->count] = item;
	(pq->priorities)[pq->count] = priority;
	(pq->count)++;
}

/* Scan through all the priorities linearly and find lowest.
	NOTE: This function was written by Grady Fitzpatrick and provided in the skeletion code */
void *deletemin(struct pq *pq) {
	int i;
	int lowestElement = 0;
	void *returnVal;
	if (pq->count <= 0) {
		return NULL;
	}
	for(i = 0; i < pq->count; i++) {
		if((pq->priorities)[i] < (pq->priorities)[lowestElement]) {
			lowestElement = i;
		}
	}
	returnVal = (pq->queue)[lowestElement];
	/* Delete item from queue by swapping final item into place of deleted
		element. */
	if(pq->count > 0) {
		(pq->priorities)[lowestElement] = (pq->priorities)[pq->count - 1];
		(pq->queue)[lowestElement] = (pq->queue)[pq->count - 1];
		(pq->count)--;
	}
	return returnVal;
}

/* searches priority queue to find given item */
int inQueue(struct pq *pq, int item) {
	for(int i = 0; i < pq->count; i++) {
		if(*(int*)pq->queue[i] == item)
			return FOUND;
	}
	return MISSING;
}

/* Updates priority of an element in queue */
void update(struct pq *pq, int item, double priority) {
	for(int i = 0; i < pq->count; i++) {
		if(*(int*)(pq->queue[i]) == item) {
			pq->priorities[i] = priority;
			return;
		}
	}
}

/* Checks if empty 
	NOTE: This function was written by Grady Fitzpatrick and provided in the skeletion code */
int empty(struct pq *pq) {
	return pq->count == 0;
}

/* Frees priority queue
	NOTE: This function was written by Grady Fitzpatrick and provided in the skeletion code */
void freePQ(struct pq *pq) {
	if(! pq) {
		return;
	}
	if(pq->allocated > 0) {
		free(pq->queue);
		free(pq->priorities);
	}
	free(pq);
}
