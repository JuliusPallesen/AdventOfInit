#include <gtest/gtest.h>
#include "../src/aocutils.h"

using namespace aoc;

TEST(ParseFileAsStringVector, HandleReadFile)
{
    EXPECT_NO_FATAL_FAILURE(parseFileAsStringVector("./resource/abc.txt"));
    EXPECT_NO_THROW(parseFileAsStringVector("./resource/abc.txt"));
}

TEST(ParseFileAsStringVector, HandleParseFile)
{
    const auto sv = parseFileAsStringVector("./resource/abc.txt");
    std::vector<std::string> expected{"a", "b", "c"};
    EXPECT_EQ(sv.size(), expected.size());
    for (size_t i = 0; i < expected.size(); ++i)
    {
        EXPECT_EQ(expected[i], sv[i]);
    }
}

TEST(ParseFileAsStringVector, HandleNewLine)
{
    const auto sv = parseFileAsStringVector("./resource/new_line.txt");
    EXPECT_EQ(sv.size(), 3);
}

TEST(ParseFileAsIntVector, HandleReadFile)
{
    EXPECT_NO_FATAL_FAILURE(parseFileAsIntVector("./resource/ints.txt"));
    EXPECT_NO_THROW(parseFileAsIntVector("./resource/ints.txt"));
}

TEST(ParseFileAsIntVector, HandleReadInts)
{
    const auto iv = parseFileAsIntVector("./resource/ints.txt");
    for (size_t i = 0; i <= 10; ++i)
    {
        EXPECT_EQ(i, iv[i]);
    }
}

TEST(ParseFileAsIntVector, HandleNegatives)
{
    const auto iv = parseFileAsIntVector("./resource/negatives.txt");
    for (size_t i = 0; i < 10; ++i)
    {
        EXPECT_EQ(-1 * (i + 1), iv[i]);
    }
}

TEST(ParseFileAsIntVector, HandleNonInteger)
{
    EXPECT_ANY_THROW(parseFileAsIntVector("./resource/abc.txt"));
}

TEST(ParseFileAsVariant, HandleNoCrash)
{
    EXPECT_NO_FATAL_FAILURE(parseFileAsVariantVector("./resource/variant_hard.txt"));
    EXPECT_NO_THROW(parseFileAsVariantVector("./resource/variant_hard.txt"));
}
/*
File contents
value: 1
name: abc
100 100 000
*/
TEST(ParseFileAsVariant, HandleReadIntAndString)
{
    const auto vv = parseFileAsVariantVector("./resource/variant_easy.txt");
    EXPECT_TRUE(std::holds_alternative<std::string>(vv[0][0]));
    EXPECT_TRUE(std::holds_alternative<int>(vv[0][1]));
    EXPECT_EQ(std::get<std::string>(vv[0][0]), std::string("value:"));
    EXPECT_EQ(std::get<int>(vv[0][1]), 1);
}