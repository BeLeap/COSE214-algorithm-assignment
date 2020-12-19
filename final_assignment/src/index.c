#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/general/general.h"

bool IsExists(char*, int);

int main(int argc, char* argv[]) {
  if (argc != 2) {
    PrintError("Not enough arguments");
    return 1;
  }

  for (int i = (int)'a'; i <= (int)'z'; ++i) {
    for (int j = (int)'a'; j <= (int)'z'; ++j) {
      char indexFileName[100] = {
          0,
      };
      sprintf(indexFileName, "%c%c.index", (char)i, (char)j);
      remove(indexFileName);
      fclose(fopen(indexFileName, "w"));
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
    count++;
    fprintf(wordIdFile, "%s %d\n", buffer, count);

    for (int i = 0; i < strlen(buffer) - 1; ++i) {
      char indexFileName[100] = {
          0,
      };
      sprintf(indexFileName, "%c%c.index", buffer[i], buffer[i + 1]);
      FILE* indexFile = fopen(indexFileName, "ab");

      if (!IsExists(indexFileName, count)) {
        if (indexFile == NULL) {
          fprintf(stderr, "failed to open %s\n", indexFileName);
          perror("error");
          return 1;
        }
        fwrite(&count, sizeof(int), 1, indexFile);
      }
      fclose(indexFile);
    }

    if (!(count % 100000)) {
      printf("Currently Processing: %d\n", count);
    }
  }

  fclose(dictionary);
  fclose(wordIdFile);

  return 0;
}

bool IsExists(char* filename, int wordId) {
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    return false;
  }

  while (true) {
    if (feof(fp)) {
      return false;
    }

    int buffer;
    fread(&buffer, sizeof(int), 1, fp);
    if (buffer == wordId) {
      return true;
    }
  }
}
