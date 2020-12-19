#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

LinkedList* NewLinkedList() {
  LinkedList* newLinkedList = (LinkedList*)malloc(sizeof(LinkedList));
  newLinkedList->head = NULL;

  newLinkedList->UpdateOrInsert_Freq = LinkedListUpdateOrInsert_Freq;
  newLinkedList->Insert_Distance = LinkedListInsert_Distance;
  newLinkedList->PopMaxDataWordId_Freq = LinkedListPopMaxDataWordId_Freq;
  newLinkedList->PopHead_Distance = LinkedListPopHead_Distance;

  return newLinkedList;
}

Node* NewNode_Freq(int wordId) {
  Node* newNode = (Node*)malloc(sizeof(newNode));
  newNode->key = wordId;
  newNode->data = 1;
  return newNode;
}

void LinkedListUpdateOrInsert_Freq(LinkedList* self, int wordId) {
  Node* curr = self->head;
  if (curr == NULL) {
    Node* newNode = NewNode_Freq(wordId);
    self->head = newNode;
    return;
  }

  if (wordId > curr->key) {
    Node* newNode = NewNode_Freq(wordId);
    self->head = newNode;
    newNode->next = curr;
    return;
  }

  Node* prev = NULL;
  while (wordId < curr->key) {
    prev = curr;
    curr = curr->next;
    if (curr == NULL) {
      Node* newNode = NewNode_Freq(wordId);
      prev->next = newNode;
      return;
    }

    if (curr->key == wordId) {
      curr->data++;
      return;
    }
  }
  Node* newNode = NewNode_Freq(wordId);
  if (prev != NULL) {
    prev->next = newNode;
  } else {
    self->head = newNode;
  }
  newNode->next = curr;
  return;
}

Node* NewNode_Distance(int wordId, int distance) {
  Node* newNode = (Node*)malloc(sizeof(newNode));
  newNode->key = distance;
  newNode->data = wordId;
  return newNode;
}

void LinkedListInsert_Distance(LinkedList* self, int wordId, int distance) {
  Node* curr = self->head;
  if (curr == NULL) {
    Node* newNode = NewNode_Distance(wordId, distance);
    self->head = newNode;
    return;
  }

  if (distance < curr->key) {
    Node* newNode = NewNode_Distance(wordId, distance);
    self->head = newNode;
    newNode->next = curr;
    return;
  }

  Node* prev = NULL;
  while (distance > curr->key) {
    prev = curr;
    curr = curr->next;
    if (curr == NULL) {
      Node* newNode = NewNode_Distance(wordId, distance);
      prev->next = newNode;
      return;
    }

    if (curr->key == distance) {
      break;
    }
  }
  Node* newNode = NewNode_Distance(wordId, distance);
  if (prev != NULL) {
    prev->next = newNode;
  } else {
    self->head = newNode;
  }
  newNode->next = curr;
  return;
}

int LinkedListPopMaxDataWordId_Freq(LinkedList* self, int* freq) {
  Node* curr = self->head;
  Node* prev = NULL;

  Node* prevMaxNode = NULL;
  Node* maxNode = NULL;
  int max = 0;
  while (curr != NULL) {
    if (curr->data > max) {
      prevMaxNode = prev;
      maxNode = curr;
      max = curr->data;
    }
    prev = curr;
    curr = curr->next;
  }

  int wordId = -1;
  if (maxNode != NULL) {
    wordId = maxNode->key;
    *freq = maxNode->data;

    if (prevMaxNode == NULL) {
      self->head = maxNode->next;
    } else {
      prevMaxNode->next = maxNode->next;
    }

    free(maxNode);
  }
  return wordId;
}

int LinkedListPopHead_Distance(LinkedList* self) {
  Node* curr = self->head;
  if (curr == NULL) {
    return -1;
  }

  self->head = curr->next;

  int wordId = curr->data;
  free(curr);
  return wordId;
}
