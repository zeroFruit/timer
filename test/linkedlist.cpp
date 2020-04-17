#include "gtest/gtest.h"

extern "C" {
#include "linkedlist.h"
}

TEST(new_linked_list, ok) {
  node_t *ll = new_linked_list();
  EXPECT_TRUE(ll->item == NULL);
  EXPECT_TRUE(ll->next == NULL);
}