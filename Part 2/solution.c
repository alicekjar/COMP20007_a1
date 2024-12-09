/*
solution.c

Implementation of solution to all part of Problem 2.

Code written by Alice Kjar 
Algorithms based on pseudocode found in lecture slides
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <float.h>
#include "graph.h"
#include "pq.h"
#include "linkedList.h"

#define INF_I INT_MAX       // 'infinity' for ints
#define INF_D DBL_MAX       // 'infinity' for doubles
#define UNVISITED 0         // marker for unvisited vertex
#define STEP 1              // distance between adj nodes in unweighted graph
#define PERCENT 100.0       // to convert between percent and decimal

/* Implements modified breadth-first search to find shortest path between 
	`start` and `end` returning the distance 
	Adapted from pseudocode in lecture notes */
int partA(struct graph *g, int start, int end) {
	/* assign all depths as 0 because they are unvisited */
	int depth[g->numVertices];
	for(int i = 0; i < g->numVertices; i++)
		depth[i] = UNVISITED;
	
	/* create an empty queue */
	struct linkedList *queue = newList();

	/* start form `start` */
	insertHead(queue, start);
	depth[start]++;

	while(queue->head) {
		int cur = deleteTail(queue);
		/* iterate through edges
		note: efficiency could be improved by implementing an adjacency list */
		for(int w = 0; w < g->numEdges; w++) {
			struct edge *edge_w = g->edgeList[w];
			int adj;

			/* check if edge is between current vertex and unvisited vertex */
			if ((edge_w->start == cur && depth[adj=edge_w->end] == UNVISITED)
						|| (edge_w->end == cur && depth[adj=edge_w->start] == UNVISITED)) {
				/* distance is one step further */
				depth[adj] = depth[cur] + STEP;

				if (adj == end) {
					/* found the end! */
					freeList(queue);
					return depth[adj] - STEP;
				}
				/* queued to process all adjacent vertices */
				insertHead(queue, adj);
			}
		}
	}
	fprintf(stderr, "Error: no path found. Exiting\n");
	exit(EXIT_FAILURE);
}


/* Implements Dijkstra's Algorithm to find shortest weighted path between 
	`start` and `end` returning the distance 
	Adapted from pseudocode in lecture notes*/
int partB(struct graph *g, int start, int end) {
	/* set all distances to infinity as we don't have a path to them yet */
	int dist[g->numVertices];
	int vert[g->numVertices];
	for(int i = 0; i < g->numVertices; i++) {
		dist[i] = INF_I;
		vert[i] = i;
	}
	
	dist[start] = 0;
	/* build priory queue based on distances */
	struct pq *pQueue = newPQ();
	for(int i = 0; i < g->numVertices; i++) {
		enqueue(pQueue, &vert[i], dist[i]);
	}

	while(!empty(pQueue)) {
		/* find closest vertex */
		int cur = *(int*)deletemin(pQueue);
		for(int w = 0; w < g->numEdges; w++) {
			/* check if edge is between current vertex and unvisited vertex
			Efficiency could be improved by implementing an adjacency list */
			struct edge *edge_w = g->edgeList[w];
			int adj;
			if(edge_w->start == cur)
				adj = edge_w->end;
			else if(edge_w->end == cur)
				adj = edge_w->start;
			else
				continue;

			/* check if this path is shorter than one we've already traversed */
			if (inQueue(pQueue, adj) && (edge_w->cost + dist[cur] < dist[adj])) {
				dist[adj] = dist[cur] + edge_w->cost;
				update(pQueue, adj, dist[adj]);
			}
		}
	}
	freePQ(pQueue);
	/* want shortest path to `end` */
	return dist[end];
}

/* Implements Prim's Algorithm to find minimum spanning tree from `start` 
	returning the total of all weights 
	Adapted from pseudocode in lecture notes*/
int partC(struct graph *g, int start) {
	/* set all costs to infinity as we don't have a path to them yet */
	int cost[g->numVertices];
	int vert[g->numVertices];
	for(int i = 0; i < g->numVertices; i++) {
		cost[i] = INF_I;
		vert[i] = i;
	}

	cost[start] = 0;
	/* build priory queue based on distances */
	struct pq *pQueue = newPQ();
	for(int i = 0; i < g->numVertices; i++) {
		enqueue(pQueue, &vert[i], cost[i]);
	}

	while(!empty(pQueue)) {
		/* find closest vertex */
		int cur = *(int*)deletemin(pQueue);
		for(int w = 0; w < g->numEdges; w++) {
			struct edge *edge_w = g->edgeList[w];
			int adj;
			/* check if edge is between current vertex and unvisited vertex
			Efficiency could be improved by implementing an adjacency list */
			if(edge_w->start == cur)
				adj = edge_w->end;
			else if(edge_w->end == cur)
				adj = edge_w->start;
			else
				continue;

			/* check if this edge is shorter than one we've already traversed */
			if (inQueue(pQueue, adj) && (edge_w->cost < cost[adj])) {
				cost[adj] = edge_w->cost;
				update(pQueue, adj, cost[adj]);
			}
		}
	}
	freePQ(pQueue);
	int totalCost = 0;
	/* find total weight of minimum spanning tree */ 
	for(int i = 0; i < g->numVertices;  i++)
		totalCost += cost[i];
	return totalCost; 
}

/* Implements modified Dijkstra's Algorithm to find shortest cumulative weighted
	path between `start` and `end` returning the distance 
	Adapted from pseudocode in lecture notes */
int partD(struct graph *g, int start, int end) {
	/* set all multipliers to infinity as we don't have a path to them yet */
	double mult[g->numVertices];
	int vert[g->numVertices];
	for(int i = 0; i < g->numVertices; i++) {
		mult[i] = INF_D;
		vert[i] = i;
	}

	mult[start] = 1;

	/* build priory queue based on distances */
	struct pq *pQueue = newPQ();
	for(int i = 0; i < g->numVertices; i++) {
		enqueue(pQueue, &vert[i], mult[i]);
	}

	while(!empty(pQueue)) {
		/* find closest vertex */
		int cur = *(int*)deletemin(pQueue);
		for(int w = 0; w < g->numEdges; w++) {
			struct edge *edge_w = g->edgeList[w];
			int adj;
			/* check if edge is between current vertex and unvisited vertex
			Efficiency could be improved by implementing an adjacency list */
			if(edge_w->start == cur)
				adj = edge_w->end;
			else if(edge_w->end == cur)
				adj = edge_w->start;
			else
				continue;

			/* check if this path's multiplier is smaller than one we've already 
				traversed */
			double new_mult = (1 + edge_w->cost/PERCENT) * mult[cur];
			if (inQueue(pQueue, adj) && (new_mult < mult[adj])) {
				mult[adj] = new_mult;
				update(pQueue, adj, mult[adj]);
			}
		}
	}
	freePQ(pQueue);

	/* convert multiplier to integer percentage increase */
	int increase = (mult[end] - 1) * PERCENT;
	return increase;
}


