CC=gcc
CFLAGS=-g -Wall
OBJS=src/index.o lib/general/general.o lib/vector/vector.o lib/avl/avl.o
TARGET=index

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

index.o: src/index.c lib/general/general.o lib/avl/avl.o
general.o: lib/general/general.h lib/general/general.c
vector.o: lib/vector/vector.h lib/vector/vector.c
avl.o: lib/avl/avl.h lib/avl/avl.c

clear:
	find . -type f -name '*.o' -delete
	rm index
