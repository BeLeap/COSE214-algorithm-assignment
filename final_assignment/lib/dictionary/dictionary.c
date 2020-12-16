#include "dictionary.h"

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