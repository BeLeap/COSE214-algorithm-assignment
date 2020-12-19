#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../lib/avl/avl.h"
#include "../lib/general/general.h"

void CheckFrequency(char*);

int main(int argc, char* argv[]) {  // indexFile
  if (argc != 2) {
    PrintError("Not enough arguments");
    return 1;
  }

  FILE* freqFile = fopen("freq.txt", "w");
  fprintf(freqFile, "\0");
  fclose(freqFile);

  printf("Query Spelling Correction - Press Ctrl-C to exit");
  while (true) {
    printf(">> ");
    char input[100];
    scanf("%s", input);

    for (int i = 0; i < strlen(input) - 1; ++i) {
      char indexFileName[100];
      sprintf(indexFileName, "%s/%c%c.txt", argv[1], input[i], input[i + 1]);
      FILE* indexFile = fopen(indexFileName, "r");
      if (indexFile == NULL) {
        PrintError("Failed to open file");
        exit(1);
      }

      while (true) {
        if (feof(indexFile)) {
          break;
        }

        char buffer[100];
        fscanf(indexFile, "%s", buffer);
        CheckFrequency(buffer);
      }
    }
  }
}

void CheckFrequency(char* word) {
  FILE* freqFile = fopen("freq.txt", "a");
  FILE* tempFile = fopen("temp.txt", "w");

  bool found = false;
  while (true) {
    char buffer[100];
    int freq;
    fscanf(freqFile, "%s %d", buffer, freq);
    if (buffer == word) {
      freq++;
      found = true;
      break;
    }
    fprintf(tempFile, "%s %d", buffer, freq);
  }

  if (found == false) {
    fprintf(tempFile, "%s %d", word, 1);
  }

  remove("freq.txt");
  rename("temp.txt", "freq.txt");
}