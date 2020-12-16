#ifndef STRING_H
#define STRING_H

#include "../general/general.h"

typedef struct __String {
  char* value;
  int length;

  void (*Append)(struct __String*, char*);
  COMPARE (*Compare)(void*, void*);
} String;

String* NewString(char*);
void StringAppend(String*, char*);

COMPARE StringCompare(void*, void*);

#endif