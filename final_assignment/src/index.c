#include <stdio.h>
#include <stdlib.h>

#include "../lib/general/general.h"
#include "../lib/vector/vector.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    PrintError("Not enough arguments");
    return 1;
  }

  Vector words = NewVector();

  FILE* wordsFile = fopen(argv[1], "r");
  if (wordsFile == NULL) {
    PrintError("Failed to open file");
    return 1;
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
  return 0;
}