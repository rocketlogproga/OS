CC = gcc
CFLAGS = -c -Wall

all: parent child

parent: main.o
	$(CC) main.o -o parent
parent.o: main.c
	$(CC) $(CFLAGS) main.c
child: division.o
	$(CC) division.o -o child
division.o: division.c
	$(CC) $(CFLAGS) division.c
clean:
	rm -r *.o
	rm -r parent
	rm -r child