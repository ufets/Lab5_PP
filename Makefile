
CC = mpicc

CFLAGS = -c -Wall -std=c11 -g -o2 -I/usr/include/openmpi-x86_64/  -DNDEBUG 

LDFLAGS = 

SRCS= main.c array_functions.c

OBJS = main.o array_functions.o

all: project $(SRCS)

project: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o project
array_functions.o: array_functions.c
	$(CC) $(CFLAGS) array_functions.c -o array_functions.o
main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

clean:
	rm -rf $(OBJS)