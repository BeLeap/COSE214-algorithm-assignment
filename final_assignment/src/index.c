#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/general/general.h"
#include "../lib/linkedlist/linkedlist.h"
#include "../lib/share/share.h"
#include "../lib/string/string.h"

LinkedList* getWordsFromFile(char*);
LinkedList* generate2GramWordList(LinkedList*, LinkedList*);
bool write2GramWordsListToFile(LinkedList*, char*);

int main(int argc, char* argv[]) {
  if (argc != 3) {
    PrintError("Not enough arguments");
    return 1;
  }

  LinkedList* words = getWordsFromFile(argv[1]);
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

LinkedList* getWordsFromFile(char* filename) {
  LinkedList* words = NewLinkedList(StringCompare);

  FILE* wordsFile = fopen(filename, "r");
  if (wordsFile == NULL) {
    PrintError("Failed to open file");
    return words;
  }

  int count = 0;
  while (true) {
    if (feof(wordsFile)) {
      break;
    }
    char buffer[100];
    fscanf(wordsFile, "%s", buffer);
    String* word = NewString(buffer);
    words->Insert(words, count, (void*)word);
    count++;
  }

  fclose(wordsFile);

  return words;
}

LinkedList* generate2GramWordList(LinkedList* twoGramList, LinkedList* words) {
  String* twoGram;
  LinkedList* twoGramWordsList = NewLinkedList(StringCompare);
  for (int i = 0;
       (twoGram = twoGramList->GetDataByIndex(twoGramList, i)) != NULL; ++i) {
    String* word;
    LinkedList* wordsList = NewLinkedList(StringCompare);
    for (int j = 0; (word = words->GetDataByIndex(words, j)) != NULL; ++j) {
      if (word->Include(word, twoGram)) {
        wordsList->Insert(wordsList, j, word);
      }
    }
    twoGramWordsList->Insert(twoGramWordsList, i, wordsList);
  }

  return twoGramWordsList;
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
