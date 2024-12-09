/*
	Skeleton written by Grady Fitzpatrick for 
	COMP20007 Assignment 1 2024 Semester 1
	
	Implementation details for module which contains doubly-linked list 
	specification data structures and functions.
	
	Implemented by Alice Kjar
*/

#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct linkedListNode;

/* Defintion of linked list */
struct linkedList {
	struct linkedListNode *head;
	struct linkedListNode *tail;
};

/* Definiton of node */
struct linkedListNode {

	struct linkedListNode *next;
	struct linkedListNode *prev;

	long double x;
	long double y;
};

/* Print out each value in the list from the first value to the final value.
	Each value is printed with the format "(x, y) " where x is the x value
	set when inserting the item and y is the y value set when inserting 
	the item. */
void traverseRingForward(struct linkedList *list) {
	struct linkedListNode *cur = list->head;
	while (cur) {
		printf("(%Lf, %Lf) ", cur->x, cur->y);
		/* move to next node */
		cur = cur->next;
	}
}

/* Print out first the first item of the list, then print out each value in 
	the list from the final value to the second value.
	Each value is printed with the format "(x, y) " where x is the x value
	set when inserting the item and y is the y value set when inserting 
	the item. */
void traverseRingBackwards(struct linkedList *list) {
	/* print first item */
	struct linkedListNode *first = list->head;
	printf("(%Lf, %Lf) ", first->x, first->y);

	struct linkedListNode *cur = list->tail;
	/* move backwards through list */
	while (cur != first) {
		printf("(%Lf, %Lf) ", cur->x, cur->y);
		/* move backwards to previous node */
		cur = cur->prev;
	}


}

/* Return a new empty list. */
struct linkedList *newList() {
	/* assign memory */
	struct linkedList *list;
	list = (struct linkedList*)malloc(sizeof(*list));
	assert(list);

	/* initialise pointers */
	list->head = NULL;
	list->tail = NULL;

	return list;
}

/* Insert the given x, y pair at the head of the list */
void insertHead(struct linkedList *list, long double x, long double y) {
	/* check we have valid list */
	assert(list);

	/* make new node */
	struct linkedListNode *new_node;
	new_node = (struct linkedListNode*)malloc(sizeof(*new_node));
	assert(new_node);
	new_node->x = x;
	new_node->y = y;
	new_node->prev = NULL;

	new_node->next = list->head;
	if (list->head) {
		/* list non-empty */
		list->head->prev = new_node;
	}
	else {
		list->tail=new_node;
	}
	/* reset list head */
	list->head = new_node;
}

/* Insert the given x, y pair at the tail of the list */
void insertTail(struct linkedList *list, long double x, long double y) {
	/* check we have valid list */
	assert(list);

	/* make new node */
	struct linkedListNode *new_node;
	new_node = (struct linkedListNode*)malloc(sizeof(*new_node));
	assert(new_node);
	new_node->x = x;
	new_node->y = y;
	new_node->next = NULL;

	new_node->prev = list->tail;
	if (list->tail) {
		/* list non-empty */
		list->tail->next = new_node;
	}
	else {
		list->head=new_node;
	}
	/* reset list head */
	list->tail = new_node;
}

/* Free all items in the given list. */
void freeList(struct linkedList *list) {
	struct linkedListNode *cur = list->head;
	struct linkedListNode *next;

	/* iterate through linked list to free all elems */
	while (cur) {
		next = cur->next;
		free(cur);
		cur = next;
	}

	/* free list itself */
	free(list);
	list = NULL;
}
