#include "CircularQueue.h"
#include <gtest/gtest.h>
#include <string>

typedef ::testing::Types<int, float, std::string> TestTypes;

template <typename T>
class CircularQueueTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Setup code that runs before each test
        testQueue = new CircularQueue<T>(5);
    }

    void TearDown() override
    {
        // Cleanup code that runs after each test
        delete testQueue;
    }

    CircularQueue<T> *testQueue;
};

TYPED_TEST_SUITE(CircularQueueTest, TestTypes);

//  Test Constructor with Invalid Size
TYPED_TEST(CircularQueueTest, Constructor_InvalidSize_ThrowsException)
{
    EXPECT_THROW(CircularQueue<TypeParam> queue(2), std::invalid_argument);
}

//  Test Queue is Empty Initially
TYPED_TEST(CircularQueueTest, InitiallyEmpty)
{
    CircularQueue<TypeParam> queue(5);
    EXPECT_EQ(queue.size(), 0);
}

//  Test Enqueue and Size Update
TYPED_TEST(CircularQueueTest, EnqueueIncreasesSize)
{
    CircularQueue<TypeParam> queue(3);
    queue.enqueue(TypeParam()); // Enqueue default value
    EXPECT_EQ(queue.size(), 1);
}

//  Test Enqueue & Dequeue (Handles Different Data Types Correctly)
TYPED_TEST(CircularQueueTest, EnqueueDequeue) {
    CircularQueue<TypeParam> queue(3);
    if constexpr (std::is_same_v<TypeParam, std::string>) {
        queue.enqueue("test");
        EXPECT_EQ(queue.dequeue(), "test");
    } else {
        queue.enqueue(TypeParam{42});
        EXPECT_EQ(queue.dequeue(), TypeParam{42});
    }
}

TYPED_TEST(CircularQueueTest, OverwriteOldestData) {
    CircularQueue<TypeParam> queue(3);
    if constexpr (std::is_same_v<TypeParam, std::string>) {
        queue.enqueue("A");
        queue.enqueue("B");
        queue.enqueue("C");
        queue.enqueue("D");
        EXPECT_EQ(queue.dequeue(), "B");
    } else {
        queue.enqueue(TypeParam{1});
        queue.enqueue(TypeParam{2});
        queue.enqueue(TypeParam{3});
        queue.enqueue(TypeParam{4});
        EXPECT_EQ(queue.dequeue(), TypeParam{2});
    }
}
// Test Resize Function
TYPED_TEST(CircularQueueTest, ResizeQueue)
{
    CircularQueue<TypeParam> queue(5);
    queue.resize(10);
    EXPECT_EQ(queue.size(), 0);
}

// Numeric Only: Get Average
template <typename T>
class NumericCircularQueueTest : public ::testing::Test
{
};

typedef ::testing::Types<int, float> NumericTypes;
TYPED_TEST_SUITE(NumericCircularQueueTest, NumericTypes);

TYPED_TEST(NumericCircularQueueTest, GetAverage)
{
    CircularQueue<TypeParam> queue(4);
    queue.enqueue(static_cast<TypeParam>(10));
    queue.enqueue(static_cast<TypeParam>(20));
    queue.enqueue(static_cast<TypeParam>(30));
    EXPECT_DOUBLE_EQ(queue.getAverage(), 20.0);
}

TYPED_TEST(NumericCircularQueueTest, GetAverage_EmptyQueue)
{
    CircularQueue<TypeParam> queue(4);
    EXPECT_DOUBLE_EQ(queue.getAverage(), 0.0);
}

TYPED_TEST(CircularQueueTest, ClearQueue)
{
    CircularQueue<TypeParam> queue(3);
    if constexpr (std::is_same_v<TypeParam, std::string>)
    {
        queue.enqueue("A");
        queue.enqueue("B");
        queue.clear();
        EXPECT_EQ(queue.size(), 0);
        queue.enqueue("C");
        EXPECT_EQ(queue.dequeue(), "C");
    }
    else
    {
        queue.enqueue(TypeParam{1});
        queue.enqueue(TypeParam{2});
        queue.clear();
        EXPECT_EQ(queue.size(), 0);
        queue.enqueue(TypeParam{3});
        EXPECT_EQ(queue.dequeue(), TypeParam{3});
    }
}

template<typename T>
struct TestValueProvider {
    static T getValue(int n = 1);
};

template<>
struct TestValueProvider<std::string> {
    static std::string getValue(int n = 1) { return "Value" + std::to_string(n); }
};

template<>
struct TestValueProvider<int> {
    static int getValue(int n = 1) { return n; }
};

template<>
struct TestValueProvider<float> {
    static float getValue(int n = 1) { return static_cast<float>(n); }
};

