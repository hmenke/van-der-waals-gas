OS = $(shell uname)
ifeq ($(OS),Darwin)
	CC = gcc-mp-4.8
else
	CC = gcc
endif
CFLAGS = -Wall -Wextra -O3 --std=c99 -fopenmp
LDFLAGS= -lm -fopenmp

StatMech: simulation.o solver.o statistics.o utils.o main.o
	$(CC) $(LDFLAGS) -o StatMech simulation.o solver.o statistics.o utils.o main.o

simulation.o: simulation.c simulation.h
	$(CC) -c $(CFLAGS) -o simulation.o simulation.c

solver.o: solver.c solver.h
	$(CC) -c $(CFLAGS) -o solver.o solver.c

statistics.o: statistics.c statistics.h
	$(CC) -c $(CFLAGS) -o statistics.o statistics.c

utils.o: utils.c utils.h
	$(CC) -c $(CFLAGS) -o utils.o utils.c

main.o: main.c
	$(CC) -c $(CFLAGS) -o main.o main.c

.PHONY : clean
clean:
	$(RM) *.o StatMech

dist-clean:
	$(RM) *.o *.dat StatMech
