#include "CircularQueue.h"
#include <gtest/gtest.h>

TEST(CircularQueueTest, EnqueueDequeue)
{
    CircularQueue<int> queue(3);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    EXPECT_EQ(queue.dequeue(), 1);
    EXPECT_EQ(queue.dequeue(), 2);
}

TEST(CircularQueueTest, OverwriteOldest)
{
    CircularQueue<int> queue(3);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4); // Overwrites 1
    EXPECT_EQ(queue.dequeue(), 2);
}

TEST(CircularQueueTest, GetAverage)
{
    CircularQueue<float> queue(3);
    queue.enqueue(2.0);
    queue.enqueue(4.0);
    queue.enqueue(6.0);
    EXPECT_DOUBLE_EQ(queue.getAverage(), 4.0);
}

TEST(CircularQueueTest, StringQueue)
{
    CircularQueue<std::string> queue(3);
    queue.enqueue("hello");
    queue.enqueue("world");
    EXPECT_EQ(queue.dequeue(), "hello");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
