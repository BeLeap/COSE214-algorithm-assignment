#include <stdio.h>
#include <stdlib.h>

#include "../lib/general/general.h"
#include "../lib/vector/vector.h"

Vector getWordsFromFile(char*);

int main(int argc, char* argv[]) {
  if (argc != 2) {
    PrintError("Not enough arguments");
    return 1;
  }

  Vector words = getWordsFromFile(argv[1]);

  return 0;
}

Vector getWordsFromFile(char* filename) {
  Vector words = NewVector();

  FILE* wordsFile = fopen(filename, "r");
  if (wordsFile == NULL) {
    PrintError("Failed to open file");
    return words;
  }

  while (TRUE) {
    if (feof(wordsFile)) {
      break;
    }
    char* buffer = (char*)malloc(sizeof(char) * 100);
    fgets(buffer, sizeof(buffer), wordsFile);
    words.Push(&words, buffer);
  }

  fclose(wordsFile);

  return words;
}