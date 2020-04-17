#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

LinkedList *new_linked_list() {
  LinkedList *linked_list = (LinkedList *) malloc(sizeof(LinkedList));
  linked_list->head = NULL;
  linked_list->size = 0;
  return linked_list;
}

void push_first(LinkedList *ll, void *item) {
  Node *new_node = (Node *) malloc(sizeof(Node));
  if (ll->size == 0) {
    new_node->next = NULL;
  } else {
    Node *head = ll->head;
    new_node->next = head;
  }
  new_node->item = item;
  ll->head = new_node;
  ll->size += 1;
}

void push_last(LinkedList *ll, void *item) {
  Node *current = ll->head;
  if (current == NULL) {
    current = (Node *) malloc(sizeof(Node));
    current->item = item;
    current->next = NULL;
    ll->head = current;
    ll->size += 1;
    return;
  }
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = (Node *) malloc(sizeof(Node));
  current->next->item = item;
  current->next->next = NULL;
  ll->size += 1;
}

void *pop_first(LinkedList *ll) {
  if (ll->head == NULL) {
    return NULL;
  }
  Node *target = ll->head;
  Node *next_node = target->next;
  void *result = target->item;
  free(target);
  ll->head = next_node;
  ll->size -= 1;
  return result;
}

void *pop_last(LinkedList *ll) {
  Node *head = ll->head;
  if (head == NULL) {
    return NULL;
  }
  if (head->next == NULL) {
    void *result = head->item;
    free(head);
    ll->head = NULL;
    ll->size -= 1;
    return result;
  }

  Node *current = head;
  while (current->next->next != NULL) {
    current = current->next;
  }
  void *result = current->next->item;
  free(current->next);
  current->next = NULL;
  ll->size -= 1;
  return result;
}

void print_items(LinkedList *ll) {
  Node *current = ll->head;
  while (current != NULL) {
    printf("%s\n", current->item);
    current = current->next;
  }
}

int size(LinkedList *ll) {
  return ll->size;
}