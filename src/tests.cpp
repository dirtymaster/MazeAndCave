#include <gtest/gtest.h>

#include "Model/Cave/cave.h"
#include "Model/Maze/maze.h"

namespace s21 {
TEST(test, maze_generation) {
    for (int k = 0; k < 100; k++) {
        Maze maze;
        maze.SetRandomSize();
        maze.GeneratePerfect();

        for (int i = 0; i < maze.GetRows(); ++i) {
            for (int j = 0; j < maze.GetCols(); ++j) {
                if (i != 0 && j != 0) {
                    if (maze.GetBottomWallMatrix()[i - 1][j - 1] || maze.GetRightWallMatrix()[i - 1][j - 1])
                        continue;
                }
                if (j != 0) {
                    if (maze.GetBottomWallMatrix()[i][j - 1] || maze.GetRightWallMatrix()[i][j - 1]) continue;
                }
                if (i != maze.GetRows() - 1 || j != 0) {
                    if (maze.GetRightWallMatrix()[i + 1][j - 1]) continue;
                }
                if (i != 0) {
                    if (maze.GetBottomWallMatrix()[i - 1][j] || maze.GetRightWallMatrix()[i - 1][j]) continue;
                }
                if (maze.GetBottomWallMatrix()[i][j] || maze.GetRightWallMatrix()[i][j]) continue;
                if (i != maze.GetRows() - 1) {
                    if (maze.GetRightWallMatrix()[i + 1][j]) continue;
                }
                if (i != 0 && j != maze.GetCols() - 1) {
                    if (maze.GetBottomWallMatrix()[i - 1][j + 1]) continue;
                }
                if (j != maze.GetCols() - 1) {
                    if (maze.GetBottomWallMatrix()[i][j + 1]) continue;
                }
                FAIL();
            }
        }

        for (int i = 0; i < maze.GetRows(); ++i) {
            for (int j = 0; j < maze.GetCols(); ++j) {
                if (j != 0) {
                    if (maze.GetRightWallMatrix()[i][j - 1]) continue;
                }
                if (i != 0) {
                    if (maze.GetBottomWallMatrix()[i - 1][j]) continue;
                }
                if (maze.GetBottomWallMatrix()[i][j] || maze.GetRightWallMatrix()[i][j]) continue;
            }
        }
    }
}

TEST(test, maze_solving) {
    for (int k = 0; k < 100; k++) {
        Maze maze;
        maze.SetRandomSize();
        maze.GeneratePerfect();

        std::pair<int, int> from, to;
        from = std::make_pair(std::rand() % maze.GetRows(), std::rand() % maze.GetCols());
        to = std::make_pair(std::rand() % maze.GetRows(), std::rand() % maze.GetCols());
        while (from == to) {
            from = std::make_pair(std::rand() % maze.GetRows(), std::rand() % maze.GetCols());
            to = std::make_pair(std::rand() % maze.GetRows(), std::rand() % maze.GetCols());
        }

        std::vector<std::pair<int, int>> path = maze.SolveTheMaze(from, to);

        EXPECT_TRUE(path.size() >= 2);
        EXPECT_TRUE(path.front() == to);
        EXPECT_TRUE(path.back() == from);
    }
}

TEST(test, cave_generation) {
    Cave cave;
    cave.SetRandomSize();
    cave.GeneratePerfect();

    if (cave.GetRows() < 2 || cave.GetRows() > 50 || cave.GetCols() < 2 || cave.GetCols() > 50) FAIL();
}
}  // namespace s21

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
