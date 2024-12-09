/*
	graph.c

	Set of vertices and edges implementation.

	Implementations for helper functions for graph construction and 
	manipulation.

	Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2024
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include "graph.h"
#include "utils.h"
#include "solution.h"

#define INITIALEDGES 32

/* Creates an undirected graph with the given numVertices and no edges and
	returns a pointer to it. NumEdges is the number of expected edges. 
    NOTE: This function was written by Grady Fitzpatrick and provided in the skeletion code */
struct graph *newGraph(int numVertices) {
	struct graph *g = (struct graph *) malloc(sizeof(struct graph));
	assert(g);
	/* Initialise edges. */
	g->numVertices = numVertices;
	g->numEdges = 0;
	g->allocedEdges = 0;
	g->edgeList = NULL;
	return g;
}

/* Adds an edge to the given graph. 
    NOTE: This function was written by Grady Fitzpatrick and provided in the skeletion code */
void addEdge(struct graph *g, int start, int end, int cost) {
	assert(g);
	struct edge *newEdge = NULL;
	/* Check we have enough space for the new edge. */
	if((g->numEdges + 1) > g->allocedEdges) {
		if(g->allocedEdges == 0) {
			g->allocedEdges = INITIALEDGES;
		} else {
			(g->allocedEdges) *= 2;
		}
		g->edgeList = (struct edge **) realloc(g->edgeList,
			sizeof(struct edge *) * g->allocedEdges);
		assert(g->edgeList);
	}

	/* Create the edge */
	newEdge = (struct edge *) malloc(sizeof(struct edge));
	assert(newEdge);
	newEdge->start = start;
	newEdge->end = end;
	newEdge->cost = cost;

	/* Add the edge to the list of edges. */
	g->edgeList[g->numEdges] = newEdge;
	(g->numEdges)++;
}

/* Returns a new graph which is a deep copy of the given graph (which must be 
	freed with freeGraph when no longer used). 
	NOTE: This function was written by Grady Fitzpatrick and provided in the skeletion code */
struct graph *duplicateGraph(struct graph *g) {
	struct graph *copyGraph = (struct graph *) malloc(sizeof(struct graph));
	assert(copyGraph);
	copyGraph->numVertices = g->numVertices;
	copyGraph->numEdges = g->numEdges;
	copyGraph->allocedEdges = g->allocedEdges;
	copyGraph->edgeList = (struct edge **) malloc(sizeof(struct edge *) * g->allocedEdges);
	assert(copyGraph->edgeList || copyGraph->numEdges == 0);
	int i;
	/* Copy edge list. */
	for(i = 0; i < g->numEdges; i++) {
		struct edge *newEdge = (struct edge *) malloc(sizeof(struct edge));
		assert(newEdge);
		newEdge->start = (g->edgeList)[i]->start;
		newEdge->end = (g->edgeList)[i]->end;
		newEdge->cost = (g->edgeList)[i]->cost;
		(copyGraph->edgeList)[i] = newEdge;
	}
	return copyGraph;
}

/* Frees all memory used by graph. 
    NOTE: This function was written by Grady Fitzpatrick and provided in the skeletion code */
void freeGraph(struct graph *g) {
	int i;
	for(i = 0; i < g->numEdges; i++) {
		free((g->edgeList)[i]);
	}
	if(g->edgeList) {
		free(g->edgeList);
	}
	free(g);
}

/* See specs in header file
	NOTE: This function was written by Grady Fitzpatrick and provided in the skeletion code */
struct solution *graphSolve(struct graph *g, enum problemPart part,
	int numLocations, int startingLocation, int finalLocation) {
	struct solution *solution = (struct solution *)
		malloc(sizeof(struct solution));
	assert(solution);
	if(part == PART_A) {
		solution->damageTaken = partA(g, startingLocation, finalLocation);
	} else if(part == PART_B) {
		solution->totalCost = partB(g, startingLocation, finalLocation);
	} else if(part == PART_C) {
		solution->artisanCost = partC(g, startingLocation);
	} else {
		solution->totalPercentage = partD(g, startingLocation, finalLocation);
	}
	return solution;
}

