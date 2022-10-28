#ifndef ABSTRACT_CLASS_H
#define ABSTRACT_CLASS_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace s21 {
class AbstractClass {
public:
    virtual ~AbstractClass() {}
    void SetMazeOrCave(bool is_maze) { is_maze_ = is_maze; }
    bool GetMazeOrCave() { return is_maze_; }
    virtual void SetRandomSize() = 0;
    virtual void GeneratePerfect() = 0;
    virtual bool ParseFile(std::string path) = 0;
    virtual void ClearData() = 0;
    virtual int GetRows() = 0;
    virtual int GetCols() = 0;
    virtual void SetRows(int rows) = 0;
    virtual void SetCols(int cols) = 0;
    virtual void AllocateMemory() = 0;

private:
    bool is_maze_ = true;
};
}  // namespace s21

#endif  // ABSTRACT_CLASS_H
