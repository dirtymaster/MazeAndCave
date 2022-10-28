#ifndef MAZE_H
#define MAZE_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../abstract_class.h"

namespace s21 {
class Maze : public AbstractClass {
public:
    ~Maze();
    void SetRandomSize();
    void GeneratePerfect();
    bool ParseFile(std::string path);
    void ClearData();
    std::vector<pair> SolveTheMaze(pair from, pair to);
    bool SaveToTextFile(std::string path);

    int GetRows();
    int GetCols();
    const matrix& GetRightWallMatrix();
    const matrix& GetBottomWallMatrix();
    void SetRows(int rows);
    void SetCols(int cols);

private:
    int rows_ = 0;
    int cols_ = 0;
    matrix right_wall_matrix_;
    matrix bottom_wall_matrix_;
    matrix tmp_matrix_;

    void AllocateMemory();
    void RecursiveSearch(pair from, pair to, pair& tmp, std::vector<pair>& path);
    void AddRow(const int i);
    void AssignSets(const int i);
    void CreateRightBorders(const int i);
    void CreateBottomBorders(const int i);
    void LastRow(const int i);
    bool UpperWayIsAvailable(pair from, pair to, pair& tmp, std::vector<pair>& path,
                             std::vector<pair>::iterator& itr);
    bool LowerWayIsAvailable(pair from, pair to, pair& tmp, std::vector<pair>& path,
                             std::vector<pair>::iterator& itr);
    bool LeftWayIsAvailable(pair from, pair to, pair& tmp, std::vector<pair>& path,
                            std::vector<pair>::iterator& itr);
    bool RightWayIsAvailable(pair from, pair to, pair& tmp, std::vector<pair>& path,
                             std::vector<pair>::iterator& itr);
};
}  // namespace s21

#endif  // MAZE_H