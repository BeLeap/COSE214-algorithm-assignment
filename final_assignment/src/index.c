#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/general/general.h"

int wordList[5000000][676];

int main(int argc, char* argv[]) {
  if (argc != 2) {
    PrintError("Not enough arguments");
    return 1;
  }

  FILE* indexFileList[676];
  for (int i = (int)'a'; i <= (int)'z'; ++i) {
    for (int j = (int)'a'; j <= (int)'z'; ++j) {
      char indexFileName[100] = {
          0,
      };
      sprintf(indexFileName, "%c%c.index", (char)i, (char)j);
      remove(indexFileName);
      fclose(fopen(indexFileName, "w"));
      indexFileList[(i - 'a') * 26 + (j - 'a')] = fopen(indexFileName, "ab");
    }
  }

  FILE* dictionary = fopen(argv[1], "r");
  FILE* wordIdFile = fopen("word_id.txt", "w");

  int count = 0;
  while (true) {
    if (feof(dictionary)) {
      break;
    }

    char buffer[100];
    fscanf(dictionary, "%s", buffer);
    if (strlen(buffer) == 0) break;
    count++;
    fprintf(wordIdFile, "%s %d\n", buffer, count);

    for (int i = 0; i < strlen(buffer) - 1; ++i) {
      int bigramIndex = (buffer[i] - 'a') * 26 + (buffer[i + 1] - 'a');
      wordList[count][bigramIndex] = 1;
    }
  }

  fclose(dictionary);
  fclose(wordIdFile);

  fprintf(stderr, "writing to file...\n");
  for (int i = 0; i < 5000000; ++i) {
    for (int j = 0; j < 676; ++j) {
      if (wordList[i][j] == 1) {
        FILE* indexFile = indexFileList[j];
        if (indexFile == NULL) {
          printf("i: %d, j: %d\n", i, j);
          perror("error");
          return 1;
        }
        fwrite(&i, sizeof(int), 1, indexFile);
      }
    }
  }

  for (int i = 0; i < 676; ++i) {
    fclose(indexFileList[i]);
  }

  return 0;
}
