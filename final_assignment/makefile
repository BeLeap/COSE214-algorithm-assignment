CC=gcc
CFLAGS=-g -Wall

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

all: index search

index: src/index.o lib/general/general.o lib/linkedlist/linkedlist.o lib/string/string.o
	gcc -o index src/index.o lib/general/general.o lib/linkedlist/linkedlist.o lib/string/string.o

search: src/search.o
	gcc -o search src/search.o

index.o: src/index.c
general.o: lib/general/general.h lib/general/general.c
vector.o: lib/vector/vector.h lib/vector/vector.c
avl.o: lib/avl/avl.h lib/avl/avl.c
linkedlist.o: lib/linkedlist/linkedlist.h lib/linkedlist/linkedlist.c
string.o: lib/string/string.h lib/string/string.c
dictionary.o: lib/dictionary/dictionary.h lib/dictionary/dictionary.c

search.o: src/search.c

clear:
	find . -type f -name '*.o' -delete
	rm index
	rm resource/dist/*
