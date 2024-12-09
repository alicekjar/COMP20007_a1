/*
mergesort.c

	Implementation of modified Mergesort algorthim

	Code written by Alice Kjar 

	Algorithm based on pseudocode found in 'Introduction to the Design & 
	Analysis of Algorithms' by Anany Levitin
*/

#include <stdlib.h>
#include <assert.h>
#include "mergesort.h"
#include "convexHull.h"

/* takes two sorted lists `B` and `C` and inserts them in order into `A` */
void merge(int *B, int *C, int *A, struct vector *points, int n, int *cmp_count);

/* Comparison function which returns if v1 has a smaller polar angle than v2,
or in the case of a tie if v1 has a smaller distance than v2 */
int cmp(struct vector *v1, struct vector *v2);


/* Uses Mergesort to sort the elements of `idxs` based on the values stored in 
	`points` in ascending order */
void sortPoints(int *idxs, struct vector *points, int n, int *cmp_count) {

	if (n <= 1)
		/* list must be sorted */
		return;

	/* copy two halves of list into two separate lists */    
	int mid = n/2;
	int *B = (int*)malloc(mid * sizeof(int));
	assert(B);
	for (int i = 0; i < mid; i++) {
		B[i] = idxs[i];
	}

	int *C = (int*)malloc((n-mid) * sizeof(int));
	assert(C);
	for (int i = 0; i < n-mid; i++) {
		C[i] = idxs[mid + i];
	}

	/* recursively sort both lists */
	sortPoints(B, points, mid, cmp_count);
	sortPoints(C, points, n - mid, cmp_count);

	/* merge lists in sorted order */
	merge(B, C, idxs, points, n, cmp_count);
	free(B);
	free(C);
	B = NULL;
	C = NULL;
}

/* Takes two sorted lists `B` and `C` and inserts them in order into `A` */
void merge(int *B, int *C, int *A, struct vector *points, int n, int *cmp_count) {
	int mid = n/2;
	int i = 0;
	int j = 0;
	/* move through until reached end of one list */
	while (i < mid && j < n - mid) {
		(*cmp_count)++;
		if (cmp(&points[B[i]], &points[C[j]])) {
			/* element in B is smaller */
			A[i+j] = B[i];
			i++;
		}
		else {
			/* element in C is smaller */
			A[i+j] = C[j];
			j++;
		}
	}

	while (i < mid) {
		/* insert rest of B */
		A[i+j] = B[i];
		i++;
	}

	while (j < n - mid) {
		/* insert rest of C */
		A[i+j] = C[j];
		j++;
	}
	return;
}

/* Comparison function which returns if v1 has a smaller polar angle than v2,
	or in the case of a tie if v1 has a smaller distance than v2 */
int cmp(struct vector *v1, struct vector *v2) {
	if (v1->angle != v2->angle) {
		/* compare angle */
		return v1->angle < v2->angle;
	}
	else {
		/* calculate distance squared */
		long double d1 = (v1->x)*(v1->x) + (v1->y)*(v1->y);
		long double d2 = (v2->x)*(v2->x) + (v2->y)*(v2->y);
		return d1 < d2;
	}
}
