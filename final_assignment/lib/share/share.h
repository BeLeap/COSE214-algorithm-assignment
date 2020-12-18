#ifndef SHARE_H
#define SHARE_H

#include "../linkedlist/linkedlist.h"

LinkedList* getWordsFromFile(FILE*);
LinkedList* generate2GramList();

#endif