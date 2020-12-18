#include "string.h"

#include <stdlib.h>
#include <string.h>

String* NewString(char* value) {
  String* newString = (String*)malloc(sizeof(String));
  newString->length = strlen(value);
  newString->value = (char*)malloc(sizeof(char) * newString->length);
  strcpy(newString->value, value);

  newString->Append = StringAppend;
  newString->Compare = StringCompare;
  newString->Include = StringInclude;

  return newString;
}

void StringAppend(String* self, char* value) {
  self->length = strlen(self->value) + strlen(value);
  self->value = (char*)realloc(self->value, sizeof(char) * self->length);
  strcat(self->value, value);
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

bool StringInclude(String* self, String* target) {
  if (strstr(self->value, target->value) != NULL) {
    return true;
  }
  return false;
}