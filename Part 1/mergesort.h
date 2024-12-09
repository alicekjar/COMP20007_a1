/*
mergesort.h

	Header file containing functions needed for Mergesort algorthim

	Code written by Alice Kjar 

	Algorithm based on pseudocode found in 'Introduction to the Design & 
	Analysis of Algorithms' by Anany Levitin
*/

#ifndef MERGESORT_H
#define MERGESORT_H

/* Definition of vector */
struct vector;

/* Uses Mergesort to sort the elements of `idxs` based on the values stored in 
	`points` */
void sortPoints(int *idxs, struct vector *points, int n, int *cmp_count);


#endif
