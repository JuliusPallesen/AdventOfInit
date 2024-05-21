#include <gtest/gtest.h>
#include "../src/aocutils.h"

using namespace aoc;

TEST(Print, PrintOneDim)
{
    std::vector<int> ints{1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_NO_THROW(printVector(ints));
    EXPECT_NO_THROW(printVector(ints, ','));
    std::vector<std::string> strs{"a", "b", "c", "defghijklmnopqrstuvxyz"};
    EXPECT_NO_THROW(printVector(strs));
    EXPECT_NO_THROW(printVector(strs, ','));
    EXPECT_NO_THROW(printVector(std::vector<int>{}));
    EXPECT_NO_THROW(printVector(std::vector<int>{}, ','));
}

TEST(Print, PrintTwoDim)
{
    std::vector<std::vector<int>> ints2d{{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    EXPECT_NO_THROW(print2Dvector(ints2d));
    std::vector<std::vector<std::string>> strs2d{{"a,b,c"}, {"d", "e", "f"}, {"g", "h", "i"}};
    EXPECT_NO_THROW(print2Dvector(strs2d));
    std::vector<std::vector<std::string>> strs2d2{{"a,b,c"}, {"d"}, {}};
    EXPECT_NO_THROW(print2Dvector(strs2d2));
    std::vector<std::vector<std::string>> strs2d3{};
    EXPECT_NO_THROW(print2Dvector(strs2d3));
}