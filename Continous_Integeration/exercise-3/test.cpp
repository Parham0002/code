#include "greet.h"
#include <gtest/gtest.h>

/*TEST(mytest, emptytest)
{
    EXPECT_EQ("Hello, my friend.", greet(""));
}

TEST(mytest, nametest)
{
    EXPECT_EQ("Hello, Bob.", greet("Bob"));
}

TEST(mytest, capitalname)
{

    EXPECT_EQ("HELLO JERRY.", greet("JERRY"));
}

TEST(mytest, twonames)
{
    EXPECT_EQ("Hello, Jill and Jane.", greet("Jill, Jane"));
}

TEST(mytest, twonamescapital)
{
    EXPECT_EQ("HELLO BOB AND JANE!", greet("BOB, JANE"));
}

TEST(mytest, threenames)
{
    EXPECT_EQ("Hello, Amy, Brian, and Charlotte.", greet("Amy, Brian, Charlotte"));
}

TEST(mytest, threenamescapital)
{
    EXPECT_EQ("HELLO BRIAN, BOB, AND JANE!", greet("BRIAN, BOB, JANE"));
}

TEST(mytest, twonames_onecapital)
{
    EXPECT_EQ("Hello, Amy and Charlotte. AND HELLO BRIAN", greet("Amy, BRIAN, Charlotte"));
}

TEST(mytest, mixednames)
{
    EXPECT_EQ("Hello, Amy, Charlotte, and Jill. AND HELLO BRIAN, BOB, AND JANE!", greet("Amy, BRIAN, Charlotte, BOB, Jill, JANE"));
} */

TEST(GreetTest, HandlesEmptyName)
{
    EXPECT_EQ(greet(""), "Hello, my friend.");
}

TEST(GreetTest, HandlesSingleName)
{
    EXPECT_EQ(greet("Bob"), "Hello, Bob.");
}

TEST(GreetTest, HandlesShouting)
{
    EXPECT_EQ(greet("JERRY"), "HELLO JERRY!");
}

TEST(GreetTest, HandlesTwoNames)
{
    EXPECT_EQ(greet("Jill, Jane"), "Hello, Jill and Jane.");
    EXPECT_EQ(greet("BOB, JANE"), "HELLO BOB AND JANE!");
}

TEST(GreetTest, HandlesMultipleNames)
{
    EXPECT_EQ(greet("Amy, Brian, Charlotte"), "Hello, Amy, Brian, and Charlotte.");
    EXPECT_EQ(greet("BRIAN, BOB, JANE"), "HELLO BRIAN, BOB, AND JANE!");
}

TEST(GreetTest, HandlesMixedNames)
{
    EXPECT_EQ(greet("Amy, BRIAN, Charlotte"), "Hello, Amy and Charlotte. AND HELLO BRIAN!");
    EXPECT_EQ(greet("Amy, BRIAN, Charlotte, BOB, Jill, JANE"),
              "Hello, Amy, Charlotte, and Jill. AND HELLO BRIAN, BOB, AND JANE!");
}
