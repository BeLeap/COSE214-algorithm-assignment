#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/dictionary/dictionary.h"
#include "../lib/general/general.h"
#include "../lib/linkedlist/linkedlist.h"
#include "../lib/string/string.h"

LinkedList* getWordsFromFile(char*);
LinkedList* generate2GramList();
LinkedList* generate2GramWordList(LinkedList*, LinkedList*);

int main(int argc, char* argv[]) {
  if (argc != 2) {
    PrintError("Not enough arguments");
    return 1;
  }

  LinkedList* words = getWordsFromFile(argv[1]);
  PrintInfo("File read completed");

  LinkedList* twoGramList = generate2GramList();
  PrintInfo("Generate gram list completed");

  LinkedList* twoGramWordsList = generate2GramWordList(twoGramList, words);
  PrintInfo("Generate gram word list completed");

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

LinkedList* generate2GramList() {
  LinkedList* twoGramList = NewLinkedList(StringCompare);

  int count = 0;
  for (int i = 'a'; i < 'z'; ++i) {
    for (int j = 'a'; j < 'z'; ++j) {
      char temp[3];
      temp[0] = i;
      temp[1] = j;
      temp[2] = '\0';
      String* gram = NewString(temp);
      twoGramList->Insert(twoGramList, count, gram);
      count++;
    }
  }

  return twoGramList;
}

LinkedList* generate2GramWordList(LinkedList* twoGramList, LinkedList* words) {
  String* twoGram;
  LinkedList* twoGramWordsList = NewLinkedList(DictionaryCompare);
  for (int i = 0; (twoGram = twoGramList->Delete(twoGramList, 0)) != NULL;
       ++i) {
    String* word;
    LinkedList* wordsList = NewLinkedList(DictionaryCompare);
    for (int j = 0; (word = words->Search(words, j)) != NULL; ++j) {
      if (word->Include(word, twoGram)) {
        Dictionary* wordDict = NewDictionary(j, word);
        wordsList->Insert(wordsList, i, wordDict);
      }
    }
    Dictionary* twoGramWordsDict = NewDictionary(i, wordsList);
    twoGramWordsList->Insert(twoGramWordsList, i, twoGramWordsDict);
  }

  return twoGramWordsList;
}
