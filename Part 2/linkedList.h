/*
	Written by Grady Fitzpatrick for 
	COMP20007 Assignment 1 2024 Semester 1
	
	Header for module which contains doubly-linked list 
		specification data structures and functions.
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct linkedList {
	struct linkedListNode *head;
	struct linkedListNode *tail;
};

/* Return a new empty list. */
struct linkedList *newList();

/* Insert the given x, y pair at the head of the list */
void insertHead(struct linkedList *list, int data);

/* Insert the given x, y pair at the tail of the list */
void insertTail(struct linkedList *list, int data);

int deleteTail(struct linkedList *list);

/* Free all items in the given list. */
void freeList(struct linkedList *list);

#endif

