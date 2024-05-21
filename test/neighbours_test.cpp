#include <gtest/gtest.h>
#include "../src/aocutils.h"

using namespace aoc;

template <typename T>
bool all_unique(const std::vector<T> &vec)
{
    return std::ranges::all_of(vec, [&vec](const T &elem)
                               { return std::find(vec.begin() + std::distance(&vec[0], &elem) + 1, vec.end(), elem) == vec.end(); });
}

class Neighbours : public testing::Test
{
protected:
    std::vector<std::vector<int>> grid;
    Position2D center, origin;

    Neighbours() : grid({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}),
                   center({1, 1}),
                   origin({0, 0}) {}
};

TEST_F(Neighbours, NoCrashDefault)
{
    EXPECT_NO_FATAL_FAILURE(getPossibleNeighbours(grid, center));
    EXPECT_NO_THROW(getPossibleNeighbours(grid, center));
    EXPECT_NO_FATAL_FAILURE(getPossibleNeighbours(grid, origin));
    EXPECT_NO_THROW(getPossibleNeighbours(grid, origin));
}

TEST_F(Neighbours, NoRestrictionsCorrectAmount)
{
    EXPECT_EQ(getPossibleNeighbours(grid, center, [](const auto &p)
                                    { return true; }, VON_NEUMANN_NEIGHBOUR_DELTAS)
                  .size(),
              4);
    EXPECT_EQ(getPossibleNeighbours(grid, center, [](const auto &p)
                                    { return true; }, MOORE_NEIGHBOUR_DELTAS)
                  .size(),
              8);
}

TEST_F(Neighbours, NoRestrictionsAllUnique)
{
    const auto vn = getPossibleNeighbours(grid, center, [](const auto &p)
                                          { return true; }, VON_NEUMANN_NEIGHBOUR_DELTAS);
    const auto moore = getPossibleNeighbours(grid, center, [](const auto &p)
                                             { return true; }, MOORE_NEIGHBOUR_DELTAS);
    EXPECT_EQ(std::ranges::find(vn, center), vn.end());
    EXPECT_EQ(std::ranges::find(moore, center), moore.end());
    EXPECT_TRUE(all_unique(vn));
    EXPECT_TRUE(all_unique(moore));
}

TEST_F(Neighbours, RestrictPosition)
{
    const auto n = getPossibleNeighbours(grid, center, [](const Position2D &p)
                                         { return p.x == p.y; }, MOORE_NEIGHBOUR_DELTAS);
    EXPECT_TRUE(std::ranges::all_of(n, [this](const auto &p)
                                    { return p.x == p.y; }));
}

TEST_F(Neighbours, RestrictElement)
{
    const auto n = getPossibleNeighbours(grid, center, [this](const Position2D &p)
                                         { return at2D(grid, p) % 2 == 0; }, MOORE_NEIGHBOUR_DELTAS);
    EXPECT_TRUE(std::ranges::all_of(n, [this](const auto &p)
                                    { return at2D(grid, p) % 2 == 0; }));
}

TEST_F(Neighbours, RestricsCharacter)
{
    const std::vector<std::string> all{"...", ".#.", "..."};
    const std::vector<std::string> none{"###", "#.#", "###"};
    
    auto valid = getPossibleNeighbours(all, {1,1}, [all](const auto & p){return at2D(all,p) == '.';}, MOORE_NEIGHBOUR_DELTAS);
    EXPECT_EQ(valid.size(), 8);
    valid = getPossibleNeighbours(none, {1,1}, [none](const auto & p){return at2D(none,p) == '.';}, MOORE_NEIGHBOUR_DELTAS);
    EXPECT_EQ(valid.size(), 0);
}