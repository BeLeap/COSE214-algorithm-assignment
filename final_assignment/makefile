all: index search

index:
	gcc index.c -o index

search:
	gcc search.c -o search


debug: index-debug search-debug

index-debug:
	gcc index.c -o index -g

search-debug:
	gcc search.c -o search -g

run:
	./index words.txt
	./search index.txt

clean:
	rm index search