#ifndef TIMER_LINKEDLIST_H
#define TIMER_LINKEDLIST_H

typedef struct Node_t {
  void *item;
  struct Node_t *next;
} Node;

typedef struct LinkedList_t {
  int size;
  struct Node_t *head;
} LinkedList;

LinkedList *new_linked_list();

void push_first(LinkedList *ll, void *item);

void push_last(LinkedList *ll, void *item);

void add_by_index(LinkedList *ll, void *item, int index);

void *pop_first(LinkedList *ll);

void *pop_last(LinkedList *ll);

void *pop_by_index(LinkedList *ll, int index);

int size(LinkedList *ll);

void print_items(LinkedList *ll);

#endif //TIMER_LINKEDLIST_H
