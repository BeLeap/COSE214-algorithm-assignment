#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "../general/general.h"

typedef struct __Dictionary {
  int id;
  void* data;

  COMPARE (*Compare)(void*, void*);
} Dictionary;

Dictionary* NewDictionary(int, void*);
COMPARE DictionaryCompare(void*, void*);

#endif