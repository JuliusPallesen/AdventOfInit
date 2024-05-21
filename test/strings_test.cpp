#include <gtest/gtest.h>
#include "../src/aocutils.h"

using namespace aoc;

TEST(SplitString, HandleNoSplit)
{
    std::string input{"ABCDEF"};
    EXPECT_NO_FATAL_FAILURE(splitString(input));
    EXPECT_NO_THROW(splitString(input));
    EXPECT_NO_FATAL_FAILURE(splitString(input, 'x'));
    EXPECT_NO_THROW(splitString(input, 'x'));
    const auto split_strs = splitString(input);
    EXPECT_EQ(split_strs.size(), 1);
    EXPECT_EQ(split_strs.at(0), input);
}

TEST(SplitString, HandleSplit)
{
    std::string input{"ABC DEF"};
    EXPECT_NO_FATAL_FAILURE(splitString(input));
    EXPECT_NO_THROW(splitString(input));
    EXPECT_NO_FATAL_FAILURE(splitString(input, ' '));
    EXPECT_NO_THROW(splitString(input, ' '));
    const auto split_strs = splitString(input);
    EXPECT_EQ(split_strs.size(), 2);
    EXPECT_EQ(split_strs.at(0), "ABC");
    EXPECT_EQ(split_strs.at(1), "DEF");
    const auto split_strs2 = splitString(input, ' ');
    EXPECT_EQ(split_strs2.size(), 2);
    EXPECT_EQ(split_strs2.at(0), "ABC");
    EXPECT_EQ(split_strs2.at(1), "DEF");
}

TEST(SplitString, HandleSplitAlternativeChar)
{
    std::string input{"ABC,DEF"};
    const auto split_strs = splitString(input, ',');
    EXPECT_EQ(split_strs.size(), 2);
    EXPECT_EQ(split_strs.at(0), "ABC");
    EXPECT_EQ(split_strs.at(1), "DEF");
}

TEST(SplitString, HandleEmpty)
{
    std::string input{""};
    EXPECT_NO_FATAL_FAILURE(splitString(input));
    EXPECT_NO_THROW(splitString(input));
    const auto split_strs = splitString(input);
    EXPECT_EQ(split_strs.size(), 0);
}

TEST(SplitString, HandleMultipleSplitChars)
{
    std::string input{"ABC               DEF"};
    const auto split_strs = splitString(input);
    EXPECT_EQ(split_strs.size(), 2);
    EXPECT_EQ(split_strs.at(0), "ABC");
    EXPECT_EQ(split_strs.at(1), "DEF");
}

TEST(SplitString, HandleOnlySplitChars)
{
    std::string input{"             "};
    const auto split_strs = splitString(input);
    EXPECT_TRUE(split_strs.empty());
}

TEST(SplitString, HandleMultipleSplitStringChars)
{
    std::string input{"ABC    ,,,,  ,   DEF"};
    const auto split_strs = splitString(input, ", ");
    EXPECT_EQ(split_strs.size(), 2);
    EXPECT_EQ(split_strs.at(0), "ABC");
    EXPECT_EQ(split_strs.at(1), "DEF");
}

TEST(SplitStringByString, HandleLen1)
{
    std::string str{"abc,def,ghi"};
    std::string split{","};
    const auto res = splitStringByString(str, split);
    EXPECT_EQ(res.size(), 3);
    std::ranges::for_each(res, [](const auto &s)
                          { EXPECT_EQ(s.size(), 3); });
}

TEST(SplitStringByString, HandleLenOver1)
{
    std::string str{"abc123def123ghi"};
    std::string split{"123"};
    const auto res = splitStringByString(str, split);
    EXPECT_EQ(res.size(), 3);
    std::ranges::for_each(res, [](const auto &s)
                          { EXPECT_EQ(s.size(), 3); });
}

TEST(SplitStringByString, HandleNeline)
{
    std::string str{"abc\ndef\nghi"};
    std::string split{"\n"};
    const auto res = splitStringByString(str, split);
    EXPECT_EQ(res.size(), 3);
    std::ranges::for_each(res, [](const auto &s)
                          { EXPECT_EQ(s.size(), 3); });
}

TEST(SplitStringByString, HandleMultiple)
{
    std::string str{"abc,def,,ghi"};
    std::string split{","};
    const auto res = splitStringByString(str, split, true);
    EXPECT_EQ(res.size(), 4);
}

TEST(SplitString, HandleOnlySplitStringChars)
{
    std::string input{"abcdef"};
    const auto split_strs = splitString(input, input);
    EXPECT_TRUE(split_strs.empty());
}

TEST(JoinString, HandleJoin)
{
    std::vector<std::string> input{"a", "b", "c"};
    EXPECT_NO_THROW(joinString(input));
    EXPECT_NO_FATAL_FAILURE(joinString(input));
    const auto join_str = joinString(input);
    EXPECT_EQ(join_str.size(), 3);
    EXPECT_EQ(join_str, "abc");
}

TEST(JoinString, HandleJoinChar)
{
    std::vector<std::string> input{"a", "b", "c"};
    EXPECT_NO_THROW(joinString(input, ' '));
    EXPECT_NO_FATAL_FAILURE(joinString(input, ' '));
    const auto join_str = joinString(input, ' ');
    EXPECT_EQ(join_str.size(), 5);
    EXPECT_EQ(join_str, "a b c");
}

TEST(JoinString, HandleJoinString)
{
    std::vector<std::string> input{"a", "b", "c"};
    EXPECT_NO_THROW(joinString(input, ", "));
    EXPECT_NO_FATAL_FAILURE(joinString(input, ", "));
    const auto join_str = joinString(input, ", ");
    EXPECT_EQ(join_str, "a, b, c");
}