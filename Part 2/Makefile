# Build targets
# lm - link math library library. required if you use math.h functions (commonly
# linked by default on mac).
problem2a: problem2a.o solution.o utils.o graph.o pq.o linkedList.o
	gcc -Wall -o problem2a -g -lm problem2a.o solution.o utils.o graph.o pq.o linkedList.o

problem2b: problem2b.o solution.o utils.o graph.o pq.o linkedList.o
	gcc -Wall -o problem2b -g -lm problem2b.o solution.o utils.o graph.o pq.o linkedList.o

problem2c: problem2c.o solution.o utils.o graph.o pq.o linkedList.o
	gcc -Wall -o problem2c -g -lm problem2c.o solution.o utils.o graph.o pq.o linkedList.o

problem2d: problem2d.o solution.o utils.o graph.o pq.o linkedList.o
	gcc -Wall -o problem2d -g -lm problem2d.o solution.o utils.o graph.o pq.o linkedList.o

problem2a.o: problem2a.c graph.h utils.h
	gcc -c problem2a.c -Wall -g

problem2b.o: problem2b.c graph.h utils.h
	gcc -c problem2b.c -Wall -g

problem2c.o: problem2c.c graph.h utils.h
	gcc -c problem2c.c -Wall -g

problem2d.o: problem2d.c graph.h utils.h
	gcc -c problem2d.c -Wall -g

solution.o: solution.c solution.h graph.h pq.h
	gcc -c solution.c -Wall -g

utils.o: utils.c utils.h graph.h
	gcc -c utils.c -Wall -g

graph.o: graph.c graph.h utils.h solution.h
	gcc -c graph.c -Wall -g

pq.o: pq.c pq.h
	gcc -c pq.c -Wall -g

linkedList.o: linkedList.c linkedList.h
	gcc -c linkedList.c -Wall -g


