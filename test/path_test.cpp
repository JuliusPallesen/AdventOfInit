#include <gtest/gtest.h>
#include "../src/aocutils.h"

using namespace aoc;

class Dijkstra : public testing::Test
{
protected:
    std::vector<std::string> path1, path2, path3;
    DijkstraState state1, state2, state3;
    int path1_len, path2_len, path3_len;
    Position2D start;

    Dijkstra() : path1(std::move(parseFileAsStringVector("./resource/find_path1_len24.txt"))),
                 path1_len(24),
                 path2(std::move(parseFileAsStringVector("./resource/find_path2_len24.txt"))),
                 path2_len(24),
                 path3(std::move(parseFileAsStringVector("./resource/find_path3_no_path.txt"))),
                 path3_len(INT_MAX),
                 state1({Position2D{0, 0}, 0}),
                 state2({Position2D{1, 0}, 1}),
                 state3({Position2D{1, 1}, 2}),
                 start(Position2D{0, 0}) {}

    Position2D getEnd(const std::vector<std::string> &mep)
    {
        return Position2D{static_cast<int>(mep.size() - 1), static_cast<int>(mep.at(0).size() - 1)};
    }
};

TEST_F(Dijkstra, HandleSortByPathLength)
{
    std::priority_queue<DijkstraState> q;
    q.emplace(state3);
    q.emplace(state1);
    q.emplace(state2);
    for (auto &&i : {state1, state2, state3})
    {
        const auto state = q.top();
        q.pop();
        EXPECT_EQ(i.length, state.length);
    }
}

TEST_F(Dijkstra, HandleSimpleTest)
{
    std::vector<std::string> input{"xxx", "xxx", "xxx"};
    Position2D start{0, 0};
    const auto end = [&input](const Position2D &p)
    { return p == Position2D{2, 2}; };
    int res = dijkstra(input, start, end);
    EXPECT_EQ(res, 4);
}

TEST_F(Dijkstra, HandleSimpleTestWalls)
{
    std::vector<std::string> input{
        "...",
        "##.",
        "...",
        ".##",
        "...",
    };
    Position2D start{0, 0};
    const auto end = [&input](const Position2D &p)
    { return p == Position2D{4, 2}; };
    int res = dijkstra(input, start, end, [&input](const Position2D &p)
                       { return at2D(input, p) == '.'; });
    EXPECT_EQ(res, 10);
}

TEST_F(Dijkstra, HandleSimplePath)
{
    Position2D finish{static_cast<int>(path1.size() - 1), static_cast<int>(path1.at(0).size() - 1)};
    const auto res = dijkstra(
        path1,
        start,
        [&finish](const auto &p)
        { return p == finish; },
        [this](const auto &p)
        { return at2D(path1, p) == '.'; });
    std::cout << std::format("p1 {}\n", res);
    EXPECT_EQ(res, path1_len);
}

TEST_F(Dijkstra, HandleHarderPath)
{
    Position2D finish{static_cast<int>(path2.size() - 1), static_cast<int>(path2.at(0).size() - 1)};
    const auto res = dijkstra(
        path2,
        start,
        [&finish](const auto &p)
        { return p == finish; },
        [this](const auto &p)
        { return at2D(path2, p) == '.'; });
    std::cout << std::format("p2 {}\n", res);
    EXPECT_EQ(res, path2_len);
}

TEST_F(Dijkstra, HandleNoPath)
{
    Position2D finish{static_cast<int>(path3.size() - 1), static_cast<int>(path3.at(0).size() - 1)};
    const auto res = dijkstra(
        path3,
        start,
        [&finish](const auto &p)
        { return p == finish; },
        [this](const auto &p)
        { return at2D(path3, p) == '.'; });
    std::cout << std::format("p3 {}\n", res);
    EXPECT_EQ(res, path3_len);
}
