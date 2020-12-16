CC=gcc
CFLAGS=-g -Wall
OBJS=src/index.o lib/general/general.o lib/linkedlist/linkedlist.o lib/string/string.o
TARGET=index

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

index.o: src/index.c lib/general/general.o lib/avl/avl.o
general.o: lib/general/general.h lib/general/general.c
vector.o: lib/vector/vector.h lib/vector/vector.c lib/general/general.o
avl.o: lib/avl/avl.h lib/avl/avl.c lib/general/general.o
linkedlist.o: lib/linkedlist/linkedlist.h lib/linkedlist/linkedlist.c lib/general/general.o
string.o: lib/string/string.h lib/string/string.c

clear:
	find . -type f -name '*.o' -delete
	rm index
