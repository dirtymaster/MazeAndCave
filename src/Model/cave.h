#ifndef CAVE_H
#define CAVE_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "abstract_class.h"

namespace s21 {
class Cave : public AbstractClass {
public:
    Cave();
    ~Cave();
    void SetRandomSize();
    void GeneratePerfect();
    void NextStep(int birth_limit, int death_limit);
    bool ParseFile(std::string path);
    void ClearData();
    bool SaveToTextFile(std::string path);

    int GetRows();
    int GetCols();
    const std::vector<std::vector<int>>& GetCaveMatrix();
    void SetRows(int rows);
    void SetCols(int cols);

private:
    int rows_ = 0;
    int cols_ = 0;
    std::vector<std::vector<int>> matrix_of_cells_;
    void AllocateMemory();
};
}  // namespace s21

#endif  // CAVE_H