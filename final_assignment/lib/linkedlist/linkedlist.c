#include "linkedlist.h"

LinkedList NewLinkedList() {
  LinkedList newLinkedList;
  newLinkedList.head = NULL;
  newLinkedList.tail = NULL;

  newLinkedList.Insert = Insert;
  newLinkedList.Delete = Delete;

  return newLinkedList;
}