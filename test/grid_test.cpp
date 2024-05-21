#include <gtest/gtest.h>
#include "../src/aocutils.h"

using namespace aoc;

class Pos2D : public testing::Test
{
protected:
    Pos2D() : origin({0, 0}), origin_copy({0, 0}), point1({1, -1}), point2({-1, 1}) {}
    Position2D origin, origin_copy, point1, point2;
};

class Grid : public testing::Test
{
protected:
    Grid() : origin({0, 0}),
             point1({1, -1}),
             point2({-1, 1}),
             middle({static_cast<int>(grid.size() / 2), static_cast<int>(grid.size() / 2)}),
             grid({{"abc"}, {"def"}, {"ghi"}})
    {
    }
    std::vector<std::string> grid;
    Position2D origin, point1, point2, middle;
};

TEST_F(Pos2D, Equals)
{
    EXPECT_TRUE(origin == Position2D(0, 0));
    EXPECT_EQ(origin, Position2D(0, 0));
    EXPECT_TRUE(point2 == Position2D(-1, 1));
    EXPECT_EQ(point2, Position2D(-1, 1));
    EXPECT_NE(point2, origin);
}

TEST_F(Pos2D, Addition)
{
    EXPECT_EQ(origin + point1, point1);
    EXPECT_EQ(point1 + Position2D(-1, 1), origin);
}

TEST_F(Pos2D, Distance)
{
    EXPECT_EQ(origin.distance(point1), point1.distance(origin));
    EXPECT_EQ(origin.distance(point2), point2.distance(origin));
    EXPECT_EQ(origin.distance(point1), origin.distance(point2));
    EXPECT_EQ(origin.distance(point1), 2);
    EXPECT_EQ(point2.distance(point1), 4);
}

TEST_F(Pos2D, Hash)
{
    EXPECT_NE(origin.getHash(), point1.getHash());
    EXPECT_NE(point2.getHash(), point1.getHash());
    EXPECT_NE(origin.getHash(), point2.getHash());

    EXPECT_EQ(origin.getHash(), origin_copy.getHash());
}

TEST(Dir, HandleParseURDL)
{
    EXPECT_EQ(getDirFromCharURDL('U'), Directions::Up);
    EXPECT_EQ(getDirFromCharURDL('D'), Directions::Down);
    EXPECT_EQ(getDirFromCharURDL('L'), Directions::Left);
    EXPECT_EQ(getDirFromCharURDL('R'), Directions::Right);
    EXPECT_ANY_THROW(getDirFromCharURDL('A'));
}

TEST(Dir, HandleParseNESW)
{
    EXPECT_EQ(getDirFromCharNESW('N'), Directions::Up);
    EXPECT_EQ(getDirFromCharNESW('S'), Directions::Down);
    EXPECT_EQ(getDirFromCharNESW('W'), Directions::Left);
    EXPECT_EQ(getDirFromCharNESW('E'), Directions::Right);
    EXPECT_ANY_THROW(getDirFromCharNESW('A'));
}

TEST(Dir, HandlePrint)
{
    EXPECT_EQ(printDirection(Directions::Up), "Up");
    EXPECT_EQ(printDirection(Directions::Down), "Down");
    EXPECT_EQ(printDirection(Directions::Left), "Left");
    EXPECT_EQ(printDirection(Directions::Right), "Right");
    EXPECT_NO_THROW(printDirection(static_cast<Directions>(10)));
}

TEST(Dir, HandleOpposite)
{
    EXPECT_TRUE(opposite_directions(Directions::Left, Directions::Right));
    EXPECT_TRUE(opposite_directions(Directions::Right, Directions::Left));
    EXPECT_TRUE(opposite_directions(Directions::Up, Directions::Down));
    EXPECT_TRUE(opposite_directions(Directions::Down, Directions::Up));
}

TEST_F(Grid, isInBounds1D)
{
    std::vector<int> input{1, 2, 3};
    EXPECT_NO_THROW(isInBounds1D(input, 2));
    EXPECT_TRUE(isInBounds1D(input, 2));
    EXPECT_TRUE(isInBounds1D(input, 0));
    EXPECT_FALSE(isInBounds1D(input, 3));
    EXPECT_FALSE(isInBounds1D(input, -1));
}

TEST_F(Grid, IsInBounds2Dim)
{
    EXPECT_NO_THROW(isInBounds2D(grid, origin));
    EXPECT_TRUE(isInBounds2D(grid, origin));
    EXPECT_TRUE(isInBounds2D(grid, middle));
    EXPECT_FALSE(isInBounds2D(grid, point1));
    EXPECT_FALSE(isInBounds2D(grid, point2));
}

TEST_F(Grid, at2D)
{
    EXPECT_EQ(at2D(grid, origin), 'a');
    at2D(grid, origin) = 'x';
    EXPECT_EQ(at2D(grid, origin), 'x');
    at2D(grid, origin) = 'a';
    std::vector<std::vector<int>> ints{{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};

    for (int i = 0; i < 9; i++)
        EXPECT_EQ(at2D(ints, {i / 3, i % 3}), i);

    for (int y = 0; y < static_cast<int>(grid.size()); y++)
        for (int x = 0; x < static_cast<int>(grid.at(0).size()); x++)
            EXPECT_EQ(at2D(grid, {y, x}), grid[y][x]);
}

TEST_F(Grid, at2Ds)
{
    EXPECT_EQ(at2Ds(grid, origin), 'a');
    at2Ds(grid, origin) = 'x';
    EXPECT_EQ(at2Ds(grid, origin), 'x');
    EXPECT_ANY_THROW(at2Ds(grid, point1));
    EXPECT_ANY_THROW(at2Ds(grid, point2));
}