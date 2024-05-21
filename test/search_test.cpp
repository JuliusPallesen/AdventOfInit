#include <gtest/gtest.h>
#include "../src/aocutils.h"

using namespace aoc;

class Search : public testing::Test
{
protected:
    std::vector<std::vector<int>> ints;
    std::vector<std::vector<int>> empty;
    std::vector<std::string> strings;

    Search() : ints({{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}}),
               empty({}),
               strings({"abc", "def", "ghi", "", "jklmnopqrstuvwxyz"}) {}
};

TEST_F(Search, NoCrash)
{
    EXPECT_NO_FATAL_FAILURE(find2D(ints, 1));
    EXPECT_NO_FATAL_FAILURE(find2D(strings, 'a'));
    EXPECT_NO_FATAL_FAILURE(find2D(ints, 10000));
    EXPECT_NO_FATAL_FAILURE(find2D(strings, '!'));
}

TEST_F(Search, ItemPresent)
{
    EXPECT_TRUE(find2D(ints, 1));
    EXPECT_TRUE(find2D(strings, 'a'));
    EXPECT_EQ(*find2D(ints, 1), Position2D(0, 0));
    EXPECT_EQ(*find2D(strings, 'a'), Position2D(0, 0));
}

TEST_F(Search, ItemNotPresent)
{
    EXPECT_FALSE(find2D(ints, 10000));
    EXPECT_FALSE(find2D(strings, '!'));
}

TEST_F(Search, EmptyInput)
{
    EXPECT_NO_FATAL_FAILURE(find2D(empty, 1));
    EXPECT_FALSE(find2D(empty, 1));
}