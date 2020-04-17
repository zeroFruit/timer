#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

node_t *new_linked_list() {
  node_t *head = (node_t *) malloc(sizeof(node_t));
  if (head == NULL) {
    return head;
  }
  head->item = NULL;
  head->next = NULL;
  return head;
}

void push_first(node_t **head, void *item) {
  node_t *new_node = (node_t *) malloc(sizeof(node_t));
  if (new_node == NULL) {
    perror("push first failed");
  }
  new_node->item = item;
  new_node->next = *head;
  *head = new_node;
}

void push_last(node_t *head, void *item) {
  node_t *current = head;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = (node_t *) malloc(sizeof(node_t));
  current->item = item;
  current->next = NULL;
}

void *pop_first(node_t **head) {
  return NULL;
}

void *pop_last(node_t **head) {
  return NULL;
}

void *pop_by_index(node_t **head, int index) {
  return NULL;
}

void print() {}