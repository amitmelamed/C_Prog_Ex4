CC=gcc
AR=ar
OBJECTS_MAIN=main.o
FLAGS= -Wall -g

all: progmains
progmains: $(OBJECTS_MAIN)
	$(CC) $(FLAGS) -o graph $(OBJECTS_MAIN)
main.o: main.c
	$(CC) $(FLAGS) -c main.c 

.PHONY: clean all

clean:
	rm -f *.o *.a *.so graph
