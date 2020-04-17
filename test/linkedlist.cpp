#include "gtest/gtest.h"

extern "C" {
#include "linkedlist.h"
}

TEST(new_linked_list, ok) {
  LinkedList *ll = new_linked_list();
  EXPECT_TRUE(ll->head == nullptr);
  EXPECT_EQ(ll->size, 0);
}

TEST(push_first, ok) {
  LinkedList *ll = new_linked_list();
  char const *item1 = "item1";
  push_first(ll, (void *) item1);

  EXPECT_EQ(ll->size, 1);
  EXPECT_EQ(ll->head->item, "item1");
  EXPECT_TRUE(ll->head->next == nullptr);

  char const *item2 = "item2";
  push_first(ll, (void *) item2);
  EXPECT_EQ(ll->size, 2);
  EXPECT_EQ(ll->head->item, "item2");
  EXPECT_EQ(ll->head->next->item, "item1");
  EXPECT_TRUE(ll->head->next->next == nullptr);
}

TEST(push_last, ok) {
  LinkedList *ll = new_linked_list();
  char const *item1 = "item1";
  push_last(ll, (void *) item1);

  EXPECT_EQ(ll->size, 1);
  EXPECT_EQ(ll->head->item, "item1");
  EXPECT_TRUE(ll->head->next == nullptr);

  char const *item2 = "item2";
  push_last(ll, (void *) item2);
  EXPECT_EQ(ll->size, 2);
  EXPECT_EQ(ll->head->item, "item1");
  EXPECT_EQ(ll->head->next->item, "item2");
  EXPECT_TRUE(ll->head->next->next == nullptr);
}

LinkedList_t *setup_linked_list() {
  LinkedList *ll = new_linked_list();
  ll->size = 2;
  ll->head = (Node *) malloc(sizeof(Node));
  ll->head->item = (void *) "item1";
  ll->head->next = (Node *) malloc(sizeof(Node));
  ll->head->next->item = (void *) "item2";
  ll->head->next->next = nullptr;
  return ll;
}

TEST(pop_first, ok) {
  LinkedList *ll = setup_linked_list();
  char *result1 = (char *) pop_first(ll);
  EXPECT_EQ(strcmp(result1, "item1"), 0);

  char *result2 = (char *) pop_first(ll);
  EXPECT_EQ(strcmp(result2, "item2"), 0);

  EXPECT_TRUE(pop_first(ll) == nullptr);

  EXPECT_EQ(ll->size, 0);
  EXPECT_TRUE(ll->head == nullptr);
}

TEST(pop_last, ok) {
  LinkedList *ll = setup_linked_list();
  char *result1 = (char *) pop_last(ll);
  EXPECT_EQ(strcmp(result1, "item2"), 0);

  char *result2 = (char *) pop_last(ll);
  EXPECT_EQ(strcmp(result2, "item1"), 0);

  EXPECT_TRUE(pop_last(ll) == nullptr);

  EXPECT_EQ(ll->size, 0);
  EXPECT_TRUE(ll->head == nullptr);
}