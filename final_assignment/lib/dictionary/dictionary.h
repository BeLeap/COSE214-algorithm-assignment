#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "../general/general.h"

typedef struct __Dictionary {
  int id;
  char* word;
} Dictionary;

COMPARE DictionaryCompare(void*, void*);

#endif