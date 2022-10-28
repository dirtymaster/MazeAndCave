#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>

#include "../Model/abstract_class.h"
#include "../Model/maze.h"
#include "../Model/cave.h"

namespace s21 {
class Controller {
public:
    Controller();
    ~Controller();
    void SetMazeOrCave(bool is_maze);
    static Controller* GetInstance();
    void SetRandomSize();
    void GeneratePerfect();
    bool ParseFile(std::string path);
    void ClearData();
    std::vector<std::pair<int, int>> SolveTheMaze(std::pair<int, int> from, std::pair<int, int> to);
    bool SaveToTextFile(std::string path);

    int GetRows();
    int GetCols();
    const std::vector<std::vector<int>>& GetRightWallMatrix();
    const std::vector<std::vector<int>>& GetBottomWallMatrix();
    const std::vector<std::vector<int>>& GetCaveMatrix();
    void NextStep(int birth_limit, int death_limit);
    void SetRows(int rows);
    void SetCols(int cols);

private:
    AbstractClass* abstract_class;
    static Controller* instance_;
};
}  // namespace s21

#endif  // CONTROLLER_H
