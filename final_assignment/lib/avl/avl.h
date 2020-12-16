#ifndef _AVLH_
#define _AVLH_

#include "../general/general.h"

typedef struct __Node {
  int key;
  void *wordList;
  struct __Node *left, *right;
  int height;
} Node;

Node *Insert(Node *, int, void *);
Node *Delete(Node *, int);
int GetHeight(Node *);
Node *RotateRight(Node *);
Node *RotateLeft(Node *);
Node *RR(Node *);
Node *LL(Node *);
Node *LR(Node *);
Node *RL(Node *);
int GetBalanceFactor(Node *);

#endif