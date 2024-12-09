/*
solution.h

Header for module which contains solution functions
for each part of Problem 2.
		
Code written by Alice Kjar 
*/

/* Use struct graph in this file */
#include "graph.h"

/* Implements modified breadth-first search to find shortest path between 
	`start` and `end` returning the distance 
	Adapted from pseudocode in lecture notes*/
int partA(struct graph *g, int start, int end);

/* Implements Dijkstra's Algorithm to find shortest weighted path between 
	`start` and `end` returning the distance 
	Adapted from pseudocode in lecture notes*/
int partB(struct graph *g, int start, int end);

/* Implements Prim's Algorithm to find minimum spanning tree from `start` 
	returning the total of all weights 
	Adapted from pseudocode in lecture notes*/
int partC(struct graph *g, int start);

/* Implements modified Dijkstra's Algorithm to find shortest cumulative weighted
	path between `start` and `end` returning the distance 
	Adapted from pseudocode in lecture notes*/
int partD(struct graph *g, int start, int end);
