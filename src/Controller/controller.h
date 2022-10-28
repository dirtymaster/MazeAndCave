#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <vector>

#include "../Model/Cave/cave.h"
#include "../Model/Maze/maze.h"
#include "../Model/abstract_class.h"

namespace s21 {

class Controller {
public:
    void SetMazeOrCave(bool is_maze);
    void SetMaze();
    void SetCave();
    static Controller* GetInstance();
    void SetRandomSize();
    void GeneratePerfect();
    bool ParseFile(std::string path);
    void ClearData();
    std::vector<AbstractClass::pair> SolveTheMaze(AbstractClass::pair from, AbstractClass::pair to);
    bool SaveToTextFile(std::string path);

    int GetRows();
    int GetCols();
    const AbstractClass::matrix& GetRightWallMatrix();
    const AbstractClass::matrix& GetBottomWallMatrix();
    const AbstractClass::matrix& GetCaveMatrix();
    void NextStep(int birth_limit, int death_limit);
    void SetRows(int rows);
    void SetCols(int cols);

private:
    Controller();
    ~Controller();

    AbstractClass* abstract_class;
    static Controller* instance_;
};
}  // namespace s21

#endif  // CONTROLLER_H
