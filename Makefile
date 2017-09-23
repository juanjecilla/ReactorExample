CC = gcc
CFLAGS = -Wall -g

all: main

main: main.o reactor.o light-eh.o interruptor-eh.o

clean:
	rm -f *.o main *~
