#include "share.h"

#include "../string/string.h"

LinkedList* getWordsFromFile(FILE* wordsFile) {
  LinkedList* words = NewLinkedList(StringCompare);

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

LinkedList* generate2GramList() {
  LinkedList* twoGramList = NewLinkedList(StringCompare);

  int count = 0;
  for (int i = (int)'a'; i < (int)'z'; ++i) {
    for (int j = (int)'a'; j < (int)'z'; ++j) {
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