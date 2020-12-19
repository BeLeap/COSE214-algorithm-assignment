CC=gcc
CFLAGS=-g -Wall -std=c99

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

all: index search

index: src/index.o lib/general/general.o
	gcc -o index src/index.o lib/general/general.o

search: src/search.o lib/general/general.o lib/linkedlist/linkedlist.o
	gcc -o search src/search.o lib/general/general.o lib/linkedlist/linkedlist.o

general.o: lib/general/general.h lib/general/general.c
linkedlist.o: lib/linkedlist/linkedlist.h lib/linkedlist/linkedlist.c

index.o: src/index.c
search.o: src/search.c

clear:
	find . -type f -name '*.o' -delete
	rm index
	rm search

clear_out:
	rm *.index
	rm word_id.txt
