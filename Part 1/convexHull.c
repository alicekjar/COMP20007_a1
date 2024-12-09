/*
	Skeleton written by Grady Fitzpatrick for 
	COMP20007 Assignment 1 2024 Semester 1
	
	Header for module which contains convex hull 
		specification data structures and functions.

	Implemented by Alice Kjar
*/
#include "linkedList.h"
#include "problem.h"
#include "convexHull.h"
#include "stack.h"
#include "mergesort.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MIN_POINTS 3        // Min # of points needed for convex hull
#define HALF_PI 1.5707964   // Radian value of 90 degree angle
#define TRUE 1              // Boolean 'True'
#define FALSE 0             // Boolean 'False'


enum orientationResult {
	COLLINEAR = 0,
	CLOCKWISE = 1,
	COUNTERCLOCKWISE = 2
};


/* Finds the orientation between the three given points - calculates the angle between 
	the Middle-First vector and Middle-Final vector - if the Middle-First vector is zero-length,
	the gradient of the Middle-Final vector is instead used. 
	NOTE: This method was written by Grady Fitzpatrick and provided in the skeletion code */
enum orientationResult orientation(struct problem *p, int idxFirst, int idxMiddle, int idxFinal);

/* Finds point with smallest x-value, and smallest y-value if tied */
int leftmostPoint(struct problem *p);

/* Finds point with smallest y-value, and smallest x-value if tied */
int lowestPoint(struct problem *p);

/* Generates an array of angles between lowest and the points in p */
struct vector *getPolarAngles(struct problem *p, int lowest);


/* Finds the orientation between the three given points - calculates the angle between 
	the Middle-First vector and Middle-Final vector - if the Middle-First vector is zero-length,
	the gradient of the Middle-Final vector is instead used. 
	NOTE: This method was written by Grady Fitzpatrick and provided in the skeletion code */
enum orientationResult orientation(struct problem *p, int idxFirst, int idxMiddle, int idxFinal) {
	assert(idxFirst >= 0 && idxFirst < p->numPoints);
	assert(idxMiddle >= 0 && idxMiddle < p->numPoints);
	assert(idxFinal >= 0 && idxFinal < p->numPoints);

	/* function counts as one basic operation */
	p->operationCount++;

	/* Use cross-product to calculate turn direction. */
	long double p0x = p->pointsX[idxFirst];
	long double p0y = p->pointsY[idxFirst];

	long double p1x = p->pointsX[idxMiddle];
	long double p1y = p->pointsY[idxMiddle];

	long double p2x = p->pointsX[idxFinal];
	long double p2y = p->pointsY[idxFinal];

	/* Cross product of vectors P1P0 & P1P2 */
	long double crossProduct = (p0x - p1x) * (p2y - p1y) - (p0y - p1y) * (p2x - p1x);

	if(crossProduct == 0) {
		if(idxFirst == idxMiddle) {
			/* Special case where we are only looking for positive slope of P1P2. */
			if(p2x == p1x) {
				/* Special case: dx = 0, vertical */
				if(p2y < p1y) {
					/* Directly upwards */
					return COUNTERCLOCKWISE;
				} else if(p2y == p1y) {
					/* Same point. */
					return COLLINEAR;
				} else {
					return CLOCKWISE;
				}
			}
			long double m = (p2y - p1y) / (p2x - p1x);
			if(m >= 0) {
				return COUNTERCLOCKWISE;
			} else {
				return CLOCKWISE;
			}
			
		}
		return COLLINEAR;
	} else if(crossProduct > 0) {
		return CLOCKWISE;
	} else {
		return COUNTERCLOCKWISE;
	}
}

/* Finds point with smallest x-value, and smallest y-value if tied */
int leftmostPoint(struct problem *p) {
	int min = 0;
	/* check each point */
	for (int i = 1; i < p->numPoints; i++) {
		/* find smallest x */
		if (p->pointsX[i] < p->pointsX[min])
			min = i;
			
		/* if tied, find smallest y */
		else if (p->pointsX[i] == p->pointsX[min]
			&& p->pointsY[i] < p->pointsY[min])
			min = i;
	}
	return min;
}

/* Finds point with smallest y-value, and smallest x-value if tied */
int lowestPoint(struct problem *p) {
	int min = 0;
	/* check each point */
	for (int i = 1; i < p->numPoints; i++) {
		/* find smallest x */
		if (p->pointsY[i] < p->pointsY[min])
			min = i;
			
		/* if tied, find smallest y */
		else if (p->pointsY[i] == p->pointsY[min]
			&& p->pointsX[i] < p->pointsX[min])
			min = i;
	}
	return min;
}

/* Generates an array of the vectors from `lowest` to each point
	and their angles */
struct vector *getPolarAngles(struct problem *p, int lowest) {
	int n = p->numPoints;

	/* assign memory */
	struct vector *angles;
	angles = (struct vector*)malloc(n * sizeof(struct vector));
	assert(angles);

	for (int i = 0; i < n; i++) {
		/* calculuate distance in x and y directions */
		long double x = p->pointsX[i] - p->pointsX[lowest];
		long double y = p->pointsY[i] - p->pointsY[lowest];

		if (x == 0) {
			/* bypass divide by zero error */
			if (y == 0) {
				angles[i].angle = 0;
			}
			else {
				angles[i].angle = HALF_PI;
			}
		}
		else {
			/* calculate angle */
			angles[i].angle = atan2(y,x);
		}
		angles[i].x = x;
		angles[i].y = y;
	}
	return angles;
}

/* Part A - perform Jarvis' March to construct a convex
	hull for the given problem. */
struct solution *jarvisMarch(struct problem *p) {

	struct solution *s = (struct solution *) malloc(sizeof(struct solution));
	assert(s);
	s->operationCount = 0;

	 
	/* Ensure there are at least 3 points */
	if (p->numPoints < MIN_POINTS)
		return s;
	
	/* Initialize an empty list to store convex hull points */
	s->convexHull = newList();
	
	/* Find the leftmost point (pivot) among the given points */
	int leftmost = leftmostPoint(p);
	int curr = leftmost;

	/* Repeat until we return to the starting point (leftmost) */
	int firstIter = TRUE;
	while (curr != leftmost || firstIter) {
		firstIter = FALSE;
		/* Add current point to the convex hull */
		insertTail(s->convexHull, p->pointsX[curr], p->pointsY[curr]);

		/* Find the next point 'nextPoint' such that it forms a counterclockwise
			turn with the current point and any other point in the set */
		int nextPoint = 0;
		for (int point = 1; point < p->numPoints; point++) {
			if (nextPoint == curr 
				|| orientation(p, curr, nextPoint, point) == COUNTERCLOCKWISE)
				nextPoint = point;
		}
		
		/* Set 'nextPoint' as the current point for the next iteration */
		curr = nextPoint;
	}

	s->operationCount = p->operationCount;
	/* Return the solution */
	return s;
}

/* Part B - perform Graham's Scan to construct a convex
	hull for the given problem. */
struct solution *grahamScan(struct problem *p) {
	
	struct solution *s = (struct solution *) malloc(sizeof(struct solution));
	assert(s);
	s->operationCount = 0;
	s->convexHull = newList();
	
	/* Ensure there are at least 3 points */
	if (p->numPoints < MIN_POINTS)
		return s;

	/* Find the point with the lowest y-coordinate */
	int lowest = lowestPoint(p);
	
	struct vector *angles = getPolarAngles(p, lowest);

	/* Make an array of indexes to the points in p */
	int *idxs = (int*)malloc(p->numPoints * sizeof(int));
	assert(idxs);
	for (int i = 0; i < p->numPoints; i++) {
		idxs[i] = i;
	}

	/* Sort the points based on their polar angles with respect to the
		lowest point */
	sortPoints(idxs, angles, p->numPoints, &s->operationCount);
	free(angles);
	angles = NULL;
															   
	/* Initialize an empty stack to store convex hull points
	and push the first three points to the stack */
	struct stack *hull = createStack(&idxs[0]);
	push(&hull, &idxs[1]);
	push(&hull, &idxs[2]);

	/* Iterate over the remaining points */
	for (int i = 3; i < p->numPoints; i++) {
		
		/* While the current point and the two points below the top of the stack
		make a non-left turn, pop the top of the stack */
		while (orientation(p, *(int*)hull->below->item, *(int*)hull->item, idxs[i]) != COUNTERCLOCKWISE){
			pop(&hull);
		}
		/* Push the current point to the stack */
		push(&hull, &idxs[i]);
	}
	
	while (hull) {
		/* return solution in clockwise order starting at lowest*/
		int idx = *(int*)pop(&hull);
		if (idx == lowest)
			insertHead(s->convexHull, p->pointsX[idx], p->pointsY[idx]);

		else
			insertTail(s->convexHull, p->pointsX[idx], p->pointsY[idx]);
	}
	free(idxs);
	idxs = NULL;
	return s;
}


/* Frees solution structure and all contained information.
	NOTE: This method was written by Grady Fitzpatrick and provided in the skeletion code */
void freeSolution(struct solution *s) {
	if(! s) {
		return;
	}
	if(s->convexHull) {
		freeList(s->convexHull);
	}
	free(s);
}

