CC=gcc
CFLAGS=-g -Wall
OBJS=index.o lib/print/print.o lib/redblacktree/redblacktree.o
TARGET=index

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

index.o: index.c lib/print/print.o lib/redblacktree/redblacktree.o
print.o: lib/print/print.h lib/print/print.c
redblacktree.o: lib/redblacktree/redblacktree.h lib/redblacktree/redblacktree.c

clear:
	find . -type f -name '*.o' -delete
