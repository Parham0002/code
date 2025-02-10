#include "LinkedList.h"
#include <gtest/gtest.h>

class LinkedListTest : public ::testing::Test
{
protected:
    LinkedList list;
};

TEST_F(LinkedListTest, InsertAndSize)
{
    EXPECT_TRUE(list.insert(5));
    EXPECT_EQ(list.size(), 1);

    EXPECT_TRUE(list.insert(10));
    EXPECT_EQ(list.size(), 2);

    // Duplicate value should not be inserted
    EXPECT_FALSE(list.insert(10));
    EXPECT_EQ(list.size(), 2);
}

TEST_F(LinkedListTest, Search)
{
    list.insert(5);
    list.insert(10);

    auto pos = list.search(5);
    ASSERT_TRUE(pos.has_value());
    EXPECT_EQ(pos.value(), 1);

    pos = list.search(10);
    ASSERT_TRUE(pos.has_value());
    EXPECT_EQ(pos.value(), 2);

    // Value not found
    EXPECT_FALSE(list.search(20).has_value());
}

TEST_F(LinkedListTest, Remove)
{
    list.insert(5);
    list.insert(10);
    EXPECT_TRUE(list.remove(5));
    EXPECT_EQ(list.size(), 1);

    // Removing non-existing value
    EXPECT_FALSE(list.remove(20));
}

TEST_F(LinkedListTest, Edit)
{
    list.insert(5);
    list.insert(10);

    // Edit to a unique, valid value
    EXPECT_TRUE(list.edit(5, 15));
    EXPECT_TRUE(list.search(15).has_value());
    EXPECT_FALSE(list.search(5).has_value());

    // Edit to an existing value (invalid)
    EXPECT_FALSE(list.edit(10, 15));
}

TEST_F(LinkedListTest, Clear)
{
    list.insert(5);
    list.insert(10);
    list.clear();
    EXPECT_EQ(list.size(), 0);
    EXPECT_FALSE(list.search(5).has_value());
}
