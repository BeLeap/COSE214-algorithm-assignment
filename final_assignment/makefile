CC=gcc
CFLAGS=-g -Wall -std=c99

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

all: index search

index: src/index.o
	gcc -o index src/index.o

search: src/search.o
	gcc -o search src/search.o

index.o: src/index.c
search.o: src/search.c

clear:
	find . -type f -name '*.o' -delete
	rm index
	rm search

clear_out:
	rm *.index
	rm word_id.txt
