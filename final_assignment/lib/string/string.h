#ifndef STRING_H
#define STRING_H

#include <stdbool.h>

#include "../general/general.h"

typedef struct __String {
  char* value;
  int length;

  void (*Append)(struct __String*, char*);
  COMPARE (*Compare)(void*, void*);
  bool (*Include)(struct __String*, struct __String*);
} String;

String* NewString(char*);
void StringAppend(String*, char*);
COMPARE StringCompare(void*, void*);
bool StringInclude(String*, String*);

#endif