#include "greet.h"
#include <gtest/gtest.h>

TEST(mytest, emptytest)
{
    EXPECT_EQ("Hello, my friend.", greet(""));
}

TEST(mytest, nametest)
{
    EXPECT_EQ("Hello, Bob.", greet("Bob"));
}

TEST(mytest, capitalname){

    EXPECT_EQ("HELLO JERRY.", greet("JERRY"));
}

TEST(mytest, twonames){
    EXPECT_EQ("Hello, Jill and Jane.", greet("Jill, Jane"));
}