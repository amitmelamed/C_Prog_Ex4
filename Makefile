.PHONY: all clean loopd loops recursived recursives 

CC = gcc
AR = ar -rcs
FLAGS = -Wall -g

###creation of .o files:###
main.o: main.c
	$(CC) $(FLAGS) -c main.c

###finished files###
graph: main.o
	$(CC) $(FLAGS) main.o -o graph

###utilitis###
all: graph

clean:
	rm -f *.o *.a *.so graph
