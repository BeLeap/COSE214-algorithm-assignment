#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/general/general.h"
#include "../lib/linkedlist/linkedlist.h"
#include "../lib/share/share.h"
#include "../lib/string/string.h"

LinkedList* generate2GramWordList(LinkedList*, LinkedList*);
bool write2GramWordsListToFile(LinkedList*, char*);

int main(int argc, char* argv[]) {
  if (argc != 3) {
    PrintError("Not enough arguments");
    return 1;
  }

  LinkedList* words = getWordsFromFile(fopen(argv[1], "r"));
  PrintInfo("File read completed");

  LinkedList* twoGramList = generate2GramList();
  PrintInfo("Generate gram list completed");

  LinkedList* twoGramWordsList = generate2GramWordList(twoGramList, words);
  PrintInfo("Generate gram word list completed");

  if (!write2GramWordsListToFile(twoGramWordsList, argv[2])) {
    return 1;
  }

  return 0;
}

bool write2GramWordsListToFile(LinkedList* twoGramWordsList, char* dirname) {
  char listFileName[100];
  LinkedList* twoGram;
  for (int i = 0; (twoGram = twoGramWordsList->GetDataByIndex(twoGramWordsList,
                                                              i)) != NULL;
       ++i) {
    strcpy(listFileName, "\0");
    strcat(listFileName, dirname);
    char fileId[5];
    sprintf(fileId, "%d", i);
    strcat(listFileName, "/");
    strcat(listFileName, fileId);
    strcat(listFileName, ".txt");
    FILE* wordListFile = fopen(listFileName, "w");

    fprintf(wordListFile, "%d\n", i);

    int key;
    for (int j = 0; (key = twoGram->GetKeyByIndex(twoGram, j)) != -1; ++j) {
      fprintf(wordListFile, "%d\n", key);
    }

    fclose(wordListFile);
  }
}
