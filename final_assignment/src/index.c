#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/general/general.h"

bool IsExists(char*, char*);

int main(int argc, char* argv[]) {
  if (argc != 3) {
    PrintError("Not enough arguments");
    return 1;
  }

  for (int i = (int)'a'; i <= 'z'; ++i) {
    for (int j = (int)'a'; j <= 'z'; ++j) {
      char distFileName[100] = {
          0,
      };
      sprintf(distFileName, "%s/%c%c.txt", argv[2], (char)i, (char)j);

      FILE* indexFile = fopen(distFileName, "w");
      fprintf(indexFile, "\0");
      fclose(indexFile);
    }
  }

  FILE* dictionary = fopen(argv[1], "r");

  while (true) {
    if (feof(dictionary)) {
      break;
    }

    char buffer[100];
    fscanf(dictionary, "%s", buffer);

    for (int i = 0; i < strlen(buffer) - 1; ++i) {
      char distFileName[100] = {
          0,
      };
      sprintf(distFileName, "%s/%c%c.txt", argv[2], buffer[i], buffer[i + 1]);

      if (!IsExists(distFileName, buffer)) {
        FILE* indexFile = fopen(distFileName, "a");
        if (indexFile == NULL) {
          PrintError("Failed to open file");
          continue;
        }
        setvbuf(indexFile, NULL, _IONBF, 0);
        // printf("%s\n", buffer);
        fprintf(indexFile, "%s\n", buffer);
        fclose(indexFile);
      }
    }
  }

  fclose(dictionary);

  return 0;
}

bool IsExists(char* filename, char* word) {
  FILE* fp = fopen(filename, "r");
  while (true) {
    if (feof(fp)) {
      return false;
    }

    char buffer[100];
    fscanf(fp, "%s", buffer);
    if (!strcmp(buffer, word)) {
      return true;
    }
  }
}
