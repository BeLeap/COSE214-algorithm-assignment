#include "string.h"

#include <stdlib.h>
#include <string.h>

String* NewString(char* value) {
  String* newString = (String*)malloc(sizeof(String));
  newString->value = strdup(value);
  newString->length = strlen(value);

  newString->Append = StringAppend;

  return newString;
}

void StringAppend(String* self, char* value) {
  self->length = strlen(self->value) + strlen(value);
  self->value = strdup(strcat(self->value, value));
}

COMPARE StringCompare(void* a, void* b) {
  char* aValue = ((String*)a)->value;
  char* bValue = ((String*)b)->value;
  int result = strcmp(aValue, bValue);

  if (result < 0) {
    return SMALLER;
  } else if (result > 0) {
    return BIGGER;
  } else {
    return EQUAL;
  }
}