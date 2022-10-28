#include "controller.h"

namespace s21 {
Controller* Controller::instance_ = nullptr;
Controller::Controller() { abstract_class = new Maze;}
Controller::~Controller() {
    if (abstract_class) delete abstract_class;
}
Controller* Controller::GetInstance() {
    if (!instance_) instance_ = new Controller;
    return instance_;
}
void Controller::SetMazeOrCave(bool is_maze) {
    if (abstract_class->GetMazeOrCave() != is_maze) {
        delete abstract_class;
        if (is_maze)
            abstract_class = new Maze;
        else
            abstract_class = new Cave;
        abstract_class->SetMazeOrCave(is_maze);
    }
}
void Controller::SetRandomSize() { abstract_class->SetRandomSize(); }
void Controller::GeneratePerfect() { abstract_class->GeneratePerfect(); }
bool Controller::ParseFile(std::string path) { return abstract_class->ParseFile(path); }
void Controller::ClearData() { abstract_class->ClearData(); }
std::vector<std::pair<int, int>> Controller::SolveTheMaze(std::pair<int, int> from, std::pair<int, int> to) {
    return ((Maze*)abstract_class)->SolveTheMaze(from, to);
}
bool Controller::SaveToTextFile(std::string path) { return abstract_class->SaveToTextFile(path); }
int Controller::GetRows() { return abstract_class->GetRows(); }
int Controller::GetCols() { return abstract_class->GetCols(); }
const std::vector<std::vector<int>>& Controller::GetRightWallMatrix() {
    return ((Maze*)abstract_class)->GetRightWallMatrix();
}
const std::vector<std::vector<int>>& Controller::GetBottomWallMatrix() {
    return ((Maze*)abstract_class)->GetBottomWallMatrix();
}
const std::vector<std::vector<int>>& Controller::GetCaveMatrix() {
    return ((Cave*)abstract_class)->GetCaveMatrix();
}
void Controller::NextStep(int birth_limit, int death_limit) {
    ((Cave*)abstract_class)->NextStep(birth_limit, death_limit);
}
void Controller::SetRows(int rows) { return abstract_class->SetRows(rows); }
void Controller::SetCols(int cols) { return abstract_class->SetCols(cols); }
}  // namespace s21
