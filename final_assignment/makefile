CC=gcc
CFLAGS=-g -Wall
OBJS=src/index.o lib/general/general.o lib/avl/avl.o
TARGET=index

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

index.o: src/index.c lib/general/general.o lib/avl/avl.o
print.o: lib/print/print.h lib/print/print.c
general.o: lib/general/general.h lib/general/general.c

clear:
	find . -type f -name '*.o' -delete
	rm index
