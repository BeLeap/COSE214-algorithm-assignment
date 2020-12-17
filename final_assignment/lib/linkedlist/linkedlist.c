#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

LinkedList* NewLinkedList(void* Compare) {
  LinkedList* newLinkedList = (LinkedList*)malloc(sizeof(LinkedList));
  newLinkedList->head = NULL;

  newLinkedList->Compare = Compare;

  newLinkedList->Insert = LinkedListInsert;
  newLinkedList->Delete = LinkedListDelete;
  newLinkedList->Search = LinkedListSearch;
  newLinkedList->GetKeyByIndex = LinkedListGetKeyByIndex;
  newLinkedList->GetDataByIndex = LinkedListGetDataByIndex;

  return newLinkedList;
}

bool LinkedListInsert(LinkedList* self, int key, void* data) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  if (newNode == NULL) {
    PrintError("Failed to allocate memory");
    return false;
  }
  newNode->key = key;
  newNode->data = data;

  if (self->head == NULL) {
    self->head = newNode;
    self->length = 1;
    return true;
  }

  Node* prev = NULL;
  Node* curr = self->head;
  while (key > curr->key) {
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

  self->length++;
  return true;
}

void* LinkedListDelete(LinkedList* self, int key) {
  Node* prev = NULL;
  Node* curr = self->head;

  if (curr == NULL) {
    return NULL;
  }

  if (curr->key == key) {
    self->head = curr->next;
    void* data = curr->data;
    free(curr);
    self->length--;
    return data;
  }

  while (key > curr->key) {
    prev = curr;
    curr = curr->next;
    if (curr == NULL) {
      return NULL;
    }
    if (key == curr->key) {
      prev->next = curr->next;
      void* data = curr->data;
      free(curr);
      self->length--;
      return data;
    }
  }
  return NULL;
}

void* LinkedListSearch(LinkedList* self, int key) {
  Node* curr = self->head;
  if (curr == NULL) {
    return NULL;
  } else if (key < 0) {
    return NULL;
  }

  if (curr->key == key) {
    return curr->data;
  } else if (curr->key > key) {
    return NULL;
  }

  while (key > curr->key) {
    curr = curr->next;
    if (curr == NULL) {
      return NULL;
    }
    if (key == curr->key) {
      return curr->data;
    }
  }
  return NULL;
}

int LinkedListGetKeyByIndex(LinkedList* self, int index) {
  Node* curr = self->head;
  if (curr == NULL) {
    return -1;
  }

  if (index > self->length - 1) {
    return -1;
  }

  for (int i = 0; i < index; ++i) {
    if (curr->next == NULL) {
      return -1;
    }
    curr = curr->next;
  }
  return curr->key;
}

void* LinkedListGetDataByIndex(LinkedList* self, int index) {
  return self->Search(self, self->GetKeyByIndex(self, index));
}