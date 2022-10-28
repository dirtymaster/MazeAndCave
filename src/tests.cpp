#include <gtest/gtest.h>

#include "maze.h"

namespace s21 {
TEST(test, test) {
    for (int k = 0; k < 100; k++) {
        Maze maze;
        maze.SetRandomSize();
        maze.GeneratePerfectMaze();

        std::pair<int, int> from, to;
        from =
            std::make_pair(std::rand() % maze.rows_, std::rand() % maze.cols_);
        to = std::make_pair(std::rand() % maze.rows_, std::rand() % maze.cols_);
        while (from == to) {
            from = std::make_pair(std::rand() % maze.rows_,
                                  std::rand() % maze.cols_);
            to = std::make_pair(std::rand() % maze.rows_,
                                std::rand() % maze.cols_);
        }

        std::vector<std::pair<int, int>> path = maze.SolveTheMaze(from, to);

        for (unsigned long int i = 0; i < path.size(); i++) {
            if (path[i] == path[i + 1] ||
                (i != path.size() - 1 &&
                 ((path[i].second == path[i + 1].second &&
                   ((path[i].first < path[i + 1].first &&
                     path[i + 1].first - path[i].first > 1) ||
                    (path[i].first > path[i + 1].first &&
                     path[i].first - path[i + 1].first > 1))) ||
                  (path[i].first == path[i + 1].first &&
                   ((path[i].second < path[i + 1].second &&
                     path[i + 1].second - path[i].second > 1) ||
                    (path[i].second > path[i + 1].second &&
                     path[i].second - path[i + 1].second > 1)))))) {
                FAIL();
            }
        }
    }
}
}  // namespace s21

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
