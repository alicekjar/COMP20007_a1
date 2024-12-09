problem1a: problem1a.o problem.o stack.o convexHull.o linkedList.o mergesort.o
	gcc -Wall -o problem1a problem1a.o problem.o stack.o convexHull.o linkedList.o mergesort.o -g -lm

problem1b: problem1b.o problem.o stack.o convexHull.o linkedList.o mergesort.o
	gcc -Wall -o problem1b problem1b.o problem.o stack.o convexHull.o linkedList.o mergesort.o -g -lm
	
problem1a.o: problem1a.c problem.h stack.h linkedList.h
	gcc -c problem1a.c -Wall -g

problem1b.o: problem1b.c problem.h stack.h linkedList.h
	gcc -c problem1b.c -Wall -g

problem.o: problem.c problem.h stack.h linkedList.h
	gcc -c problem.c -Wall -g

stack.o: stack.c stack.h
	gcc -c stack.c -Wall -g

linkedList.o: linkedList.c linkedList.h
	gcc -c linkedList.c -Wall -g

convexHull.o: convexHull.c convexHull.h linkedList.h problem.h stack.h mergesort.h
	gcc -c convexHull.c -Wall -g

mergesort.o: mergesort.c mergesort.h convexHull.h
	gcc -c mergesort.c -Wall -g
