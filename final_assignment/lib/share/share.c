#include "share.h"

#include "../string/string.h"

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