#include "greet.h"
#include <gtest/gtest.h>

TEST(mytest, emptytest)
{
    EXPECT_EQ("Hello, my friend.", greet(""));
}

TEST(mytest, nametest)
{
    EXPECT_EQ("Hello,Bob.", greet("Bob"));
}
