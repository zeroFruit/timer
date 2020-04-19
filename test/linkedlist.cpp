#include "gtest/gtest.h"

extern "C" {
#include "linkedlist.h"
}

class LinkedListTest : public ::testing::Test {
private:
  LinkedList_t *setup_linked_list() {
    LinkedList *ll = new_linked_list();
    ll->size = 3;
    ll->head = (Node *) malloc(sizeof(Node));
    ll->head->item = (void *) "item1";
    ll->head->next = (Node *) malloc(sizeof(Node));
    ll->head->next->item = (void *) "item2";
    ll->head->next->next = (Node *) malloc(sizeof(Node));
    ll->head->next->next->item = (void *) "item3";
    ll->head->next->next->next = nullptr;
    return ll;
  }

  void teardown_linked_list(LinkedList *ll) {
    Node *prev = nullptr;
    Node *current = ll->head;
    if (ll->size == 0) {
      return;
    }
    while (current != nullptr) {
      prev = current;
      current = current->next;
      free(prev);
    }
  }
protected:
  virtual void SetUp() {
    ll = setup_linked_list();
  }

  virtual void TearDown() {
    teardown_linked_list(ll);
  }

  LinkedList *ll;
};

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

TEST_F(LinkedListTest, pop_first_ok) {
  char *result1 = (char *) pop_first(ll);
  EXPECT_EQ(strcmp(result1, "item1"), 0);

  char *result2 = (char *) pop_first(ll);
  EXPECT_EQ(strcmp(result2, "item2"), 0);

  char *result3 = (char *) pop_first(ll);
  EXPECT_EQ(strcmp(result2, "item2"), 0);

  EXPECT_TRUE(pop_first(ll) == nullptr);

  EXPECT_EQ(ll->size, 0);
  EXPECT_TRUE(ll->head == nullptr);
}

TEST_F(LinkedListTest, pop_last_ok) {
  char *result1 = (char *) pop_last(ll);
  EXPECT_EQ(strcmp(result1, "item3"), 0);

  char *result2 = (char *) pop_last(ll);
  EXPECT_EQ(strcmp(result2, "item2"), 0);

  char *result3 = (char *) pop_last(ll);
  EXPECT_EQ(strcmp(result3, "item1"), 0);

  EXPECT_TRUE(pop_last(ll) == nullptr);

  EXPECT_EQ(ll->size, 0);
  EXPECT_TRUE(ll->head == nullptr);
}

TEST_F(LinkedListTest, pop_by_index_when_index_is_out_of_bound) {
  void *result = pop_by_index(ll, 999);
  EXPECT_TRUE(result == nullptr);
}

TEST_F(LinkedListTest, pop_by_index_when_index_is_zero) {
  char *result = (char *) pop_by_index(ll, 0);
  EXPECT_EQ(strcmp(result, "item1"), 0);
  EXPECT_EQ(ll->size, 2);
  EXPECT_EQ(strcmp((char *) ll->head->item, "item2"), 0);
}

TEST_F(LinkedListTest, pop_by_index_when_index_is_at_last) {
  char *result = (char *) pop_by_index(ll, 2);
  EXPECT_EQ(strcmp(result, "item3"), 0);
  EXPECT_EQ(ll->size, 2);
  EXPECT_EQ(strcmp((char *) ll->head->item, "item1"), 0);
  EXPECT_EQ(strcmp((char *) ll->head->next->item, "item2"), 0);
  EXPECT_TRUE(ll->head->next->next == nullptr);
}

TEST_F(LinkedListTest, pop_by_index_when_index_is_in_middle) {
  char *result = (char *) pop_by_index(ll, 1);
  EXPECT_EQ(strcmp(result, "item2"), 0);
  EXPECT_EQ(ll->size, 2);
  EXPECT_EQ(strcmp((char *) ll->head->item, "item1"), 0);
  EXPECT_EQ(strcmp((char *) ll->head->next->item, "item3"), 0);
  EXPECT_TRUE(ll->head->next->next == nullptr);
}

TEST_F(LinkedListTest, add_by_index_when_index_is_out_of_bound) {
  add_by_index(ll, (void *) "item1", 9999);
  EXPECT_EQ(ll->size, 3);
}

TEST_F(LinkedListTest, add_by_index_when_index_is_zero) {
  add_by_index(ll, (void *) "new_item", 0);
  EXPECT_EQ(ll->size, 4);
  EXPECT_EQ((char *) ll->head->item, "new_item");
}

TEST_F(LinkedListTest, add_by_index_when_index_is_in_middle) {
  add_by_index(ll, (void *) "new_item", 1);
  EXPECT_EQ(ll->size, 4);
  EXPECT_EQ((char *) ll->head->next->item, "new_item");
  EXPECT_EQ((char *) ll->head->next->next->item, "item2");
}