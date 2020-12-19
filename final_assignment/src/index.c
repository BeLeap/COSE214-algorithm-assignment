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
      strcpy(distFileName, argv[2]);
      strcat(distFileName, "/");
      char twoGram[3] = {
          0,
      };
      sprintf(twoGram, "%c%c\0", (char)i, (char)j);
      strcat(distFileName, twoGram);
      strcat(distFileName, ".txt");

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
      strcpy(distFileName, argv[2]);
      strcat(distFileName, "/");
      char twoGram[3] = {
          0,
      };
      sprintf(twoGram, "%c%c\0", buffer[i], buffer[i + 1]);
      strcat(distFileName, twoGram);
      strcat(distFileName, ".txt");

      if (!IsExists(distFileName, buffer)) {
        FILE* indexFile = fopen(distFileName, "a");
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
