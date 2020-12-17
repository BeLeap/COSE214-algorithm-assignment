#include "dictionary.h"

#include <stdlib.h>

Dictionary* NewDictionary(int id, void* data) {
  Dictionary* newDictionary = (Dictionary*)malloc(sizeof(Dictionary));
  newDictionary->id = id;
  newDictionary->data = data;

  newDictionary->Compare = DictionaryCompare;

  return newDictionary;
}

COMPARE DictionaryCompare(void* a, void* b) {
  int aId = ((Dictionary*)a)->id;
  int bId = ((Dictionary*)b)->id;
  if (aId > bId) {
    return BIGGER;
  } else if (aId < bId) {
    return SMALLER;
  }

  return EQUAL;
}