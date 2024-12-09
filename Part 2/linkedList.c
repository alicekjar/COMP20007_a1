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

/* Definition of a node. */
struct linkedListNode {

	struct linkedListNode *next;
	struct linkedListNode *prev;

	int data; 
};

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

/* Insert the given integer at the head of the list */
void insertHead(struct linkedList *list, int data) {
	/* check we have valid list */
	assert(list);

	/* make new node */
	struct linkedListNode *new_node;
	new_node = (struct linkedListNode*)malloc(sizeof(*new_node));
	assert(new_node);
	new_node->data = data;
	new_node->prev = NULL;

	new_node->next = list->head;
	if (list->head != NULL) {
		/* list non-empty */
		list->head->prev = new_node;
	}
	else {
		list->tail = new_node;
	}
	/* reset list head */
	list->head = new_node;    
}

/* Insert the given integer at the tail of the list */
void insertTail(struct linkedList *list, int data) {
	/* check we have valid list */
	assert(list);

	/* make new node */
	struct linkedListNode *new_node;
	new_node = (struct linkedListNode*)malloc(sizeof(*new_node));
	assert(new_node);
	new_node->data = data;
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

/* Delete the last element in the list and return it */
int deleteTail(struct linkedList *list) {
  /* check list not empty */
  assert(list);
  if (!list->tail)
	exit(EXIT_FAILURE);

  /* get tail */
  struct linkedListNode *cur = list->tail;
  int data = cur->data;
  
  /* update list pointers */
  list->tail = cur->prev;
  free(cur);
  if (list->tail) {
	list->tail->next = NULL;    
  }
  else {
	/* list now empty */
	list->head = NULL;
  }
  return data;
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
