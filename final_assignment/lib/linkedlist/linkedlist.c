#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

LinkedList NewLinkedList() {
  LinkedList newLinkedList;
  newLinkedList.head = NULL;
  newLinkedList.tail = NULL;

  newLinkedList.Insert = LinkedListInsert;
  newLinkedList.Delete = LinkedListDelete;

  return newLinkedList;
}

BOOL LinkedListInsert(LinkedList* self, int data) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  if (newNode == NULL) {
    PrintError("Failed to allocate memory");
    return FALSE;
  }
  newNode->data = data;

  if (self->head == NULL) {
    self->head = newNode;
    self->tail = newNode;
    return TRUE;
  }

  Node* prev = NULL;
  Node* curr = self->head;
  while (curr->data < data) {
    prev = curr;
    curr = curr->next;
    if (curr == NULL) {
      break;
    }
  }

  if (curr == self->head) {
    self->head = newNode;
    newNode->next = curr;
  } else {
    prev->next = newNode;
    newNode->next = curr;
  }

  return TRUE;
}

BOOL LinkedListDelete(LinkedList* self, int data) {
  Node* prev = NULL;
  Node* curr = self->head;

  while (curr->data < data) {
    prev = curr;
    curr = curr->next;
    if (curr == NULL) {
      return FALSE;
    }
    if (curr->data == data) {
      prev->next = curr->next;
      free(curr);
      return TRUE;
    }
  }

  return UNKNOWN;
}