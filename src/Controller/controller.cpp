#include "controller.h"

namespace s21 {
Controller* Controller::instance_ = nullptr;

Controller::Controller() { abstract_class = new Maze; }

Controller::~Controller() {
    if (abstract_class) delete abstract_class;
}

Controller* Controller::GetInstance() {
    if (!instance_) instance_ = new Controller;
    return instance_;
}

void Controller::SetMaze() {
    if (!abstract_class->IsMaze()) {
        delete abstract_class;
        abstract_class = new Maze;
        abstract_class->SetMaze();
    }
}

void Controller::SetCave() {
    if (!abstract_class->IsCave()) {
        delete abstract_class;
        abstract_class = new Cave;
        abstract_class->SetCave();
    }
}

void Controller::SetRandomSize() { abstract_class->SetRandomSize(); }

void Controller::GeneratePerfect() { abstract_class->GeneratePerfect(); }

bool Controller::ParseFile(std::string path) { return abstract_class->ParseFile(path); }

void Controller::ClearData() { abstract_class->ClearData(); }

std::vector<AbstractClass::pair> Controller::SolveTheMaze(AbstractClass::pair from, AbstractClass::pair to) {
    return ((Maze*)abstract_class)->SolveTheMaze(from, to);
}

bool Controller::SaveToTextFile(std::string path) { return ((Maze*)abstract_class)->SaveToTextFile(path); }

int Controller::GetRows() { return abstract_class->GetRows(); }

int Controller::GetCols() { return abstract_class->GetCols(); }

const AbstractClass::matrix& Controller::GetRightWallMatrix() {
    return ((Maze*)abstract_class)->GetRightWallMatrix();
}

const AbstractClass::matrix& Controller::GetBottomWallMatrix() {
    return ((Maze*)abstract_class)->GetBottomWallMatrix();
}

const AbstractClass::matrix& Controller::GetCaveMatrix() { return ((Cave*)abstract_class)->GetCaveMatrix(); }

void Controller::NextStep(int birth_limit, int death_limit) {
    ((Cave*)abstract_class)->NextStep(birth_limit, death_limit);
}

void Controller::SetRows(int rows) { return abstract_class->SetRows(rows); }

void Controller::SetCols(int cols) { return abstract_class->SetCols(cols); }
}  // namespace s21
