#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "abstract_class.h"

namespace s21 {
class Maze : public AbstractClass {
public:
    Maze();
    ~Maze();
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
    void SetRows(int rows);
    void SetCols(int cols);

private:
    int rows_ = 0;
    int cols_ = 0;
    std::vector<std::vector<int>> right_wall_matrix_;
    std::vector<std::vector<int>> bottom_wall_matrix_;
    std::vector<std::vector<int>> tmp_matrix_;

    void AllocateMemory();
    void RecursiveSearch(std::pair<int, int> from, std::pair<int, int> to, std::pair<int, int>& tmp,
                         std::vector<std::pair<int, int>>& path);
};
}  // namespace s21