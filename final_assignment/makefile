CC=gcc
CFLAGS=-g -Wall
OBJS=index.o lib/general/general.o lib/redblacktree/redblacktree.o
TARGET=index

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

index.o: index.c lib/general/general.o lib/redblacktree/redblacktree.o
general.o: lib/general/general.h lib/general/general.c
redblacktree.o: lib/redblacktree/redblacktree.h lib/redblacktree/redblacktree.c
