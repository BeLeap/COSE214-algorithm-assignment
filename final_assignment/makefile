CC=gcc
CFLAGS=-g -Wall -std=c99

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

all: index search

index: src/index.o lib/general/general.o
	gcc -o index src/index.o lib/general/general.o

search: src/search.o lib/general/general.o
	gcc -o search src/search.o lib/general/general.o

general.o: lib/general/general.h lib/general/general.c

index.o: src/index.c
search.o: src/search.c

clear_out:
	rm *.txt

clear: clear_out
	find . -type f -name '*.o' -delete
	rm index
	rm search
