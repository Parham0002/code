#include <gtest/gtest.h>
#include "queue.h"
#include <string>

// Test with int
TEST(QueueTest, EnqueueDequeueInt)
{
    Queue<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.dequeue(), 10);
    EXPECT_EQ(q.dequeue(), 20);
    EXPECT_EQ(q.dequeue(), 30);
    EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, ClearInt)
{
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.clear();
    EXPECT_EQ(q.size(), 0);
}

// Test with float
TEST(QueueTest, EnqueueDequeueFloat)
{
    Queue<float> q;
    q.enqueue(1.1f);
    q.enqueue(2.2f);
    q.enqueue(3.3f);
    EXPECT_EQ(q.size(), 3);
    EXPECT_FLOAT_EQ(q.dequeue(), 1.1f);
    EXPECT_FLOAT_EQ(q.dequeue(), 2.2f);
    EXPECT_FLOAT_EQ(q.dequeue(), 3.3f);
    EXPECT_EQ(q.size(), 0);
}

// Test with std::string
TEST(QueueTest, EnqueueDequeueString)
{
    Queue<std::string> q;
    q.enqueue("one");
    q.enqueue("two");
    q.enqueue("three");
    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.dequeue(), "one");
    EXPECT_EQ(q.dequeue(), "two");
    EXPECT_EQ(q.dequeue(), "three");
    EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, ClearString)
{
    Queue<std::string> q;
    q.enqueue("test");
    q.enqueue("clear");
    q.clear();
    EXPECT_EQ(q.size(), 0);
}

// Test exceptions
TEST(QueueTest, DequeueEmptyQueue)
{
    Queue<int> q;
    EXPECT_THROW(q.dequeue(), std::runtime_error);
}
