#ifndef TIMER_LINKEDLIST_H
#define TIMER_LINKEDLIST_H

typedef struct _node_t node_t;

struct _node_t {
  void *item;
  struct _node_t *next;
};

node_t *new_linked_list();

void push_first(node_t **head, void *item);

void push_last(node_t *head, void *item);

void *pop_first(node_t **head);

void *pop_last(node_t **head);

void *pop_by_index(node_t **head, int index);

void print();

#endif //TIMER_LINKEDLIST_H
