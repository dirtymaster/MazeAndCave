#include "maze.h"

#include <ctime>
#include <iostream>

namespace s21 {
// Maze::Maze() {}
Maze::~Maze() { ClearData(); }
void Maze::ClearData() {
    right_wall_matrix_.clear();
    bottom_wall_matrix_.clear();
    tmp_matrix_.clear();

    rows_ = cols_ = 0;
}

void Maze::SetRandomSize() { rows_ = cols_ = std::rand() % 48 + 2; }

void Maze::AllocateMemory() {
    right_wall_matrix_.resize(rows_);
    for (int i = 0; i < rows_; i++) {
        right_wall_matrix_[i].resize(cols_);
    }
    bottom_wall_matrix_.resize(rows_);
    for (int i = 0; i < rows_; i++) {
        bottom_wall_matrix_[i].resize(cols_);
    }
}

void Maze::GeneratePerfect() {
    if (rows_ && cols_) {
        AllocateMemory();
        tmp_matrix_.resize(rows_);
        int counter;
        for (int i = 0; i < rows_; i++) {
            // Добавляем строку
            tmp_matrix_[i].resize(cols_);
            for (int j = 0; j < cols_; j++) {
                bottom_wall_matrix_[i][j] = right_wall_matrix_[i][j] = 0;
            }

            // Присваиваем множества
            counter = 0;
            if (i == 0) {
                for (int j = 0; j < cols_; j++, counter++) {
                    tmp_matrix_[i][j] = counter;
                }
            } else {
                for (int j = 0; j < cols_; j++) {
                    if (!bottom_wall_matrix_[i - 1][j]) {
                        tmp_matrix_[i][j] = tmp_matrix_[i - 1][j];
                    } else {
                        tmp_matrix_[i][j] = i * 100 + counter;
                        counter++;
                    }
                }
            }

            // Создаем границы справа
            for (int j = 0; j < cols_; j++) {
                if (std::rand() % 2 || j == cols_ - 1 || tmp_matrix_[i][j] == tmp_matrix_[i][j + 1]) {
                    right_wall_matrix_[i][j] = 1;
                } else {
                    int tmp_value = tmp_matrix_[i][j + 1];
                    for (int k = 0; k < cols_; k++) {
                        if (tmp_matrix_[i][k] == tmp_value) {
                            tmp_matrix_[i][k] = tmp_matrix_[i][j];
                        }
                    }
                }
            }

            // Создаем границы снизу
            if (i != rows_ - 1) {
                int wall_counter, group_counter;
                for (int j = 0; j < cols_; j++) {
                    if (j == 0 || tmp_matrix_[i][j] != tmp_matrix_[i][j - 1]) {
                        wall_counter = group_counter = 0;
                    }

                    // Если одна клетка в сете - оставить пустой
                    if ((j == 0 || tmp_matrix_[i][j] != tmp_matrix_[i][j - 1]) &&
                        (j == cols_ - 1 || tmp_matrix_[i][j] != tmp_matrix_[i][j + 1])) {
                        // Хотя бы один нижний проход во множестве
                    } else if (group_counter > 0 && wall_counter == group_counter &&
                               (j == cols_ - 1 || tmp_matrix_[i][j] != tmp_matrix_[i][j + 1])) {
                        // Рандом
                    } else if (std::rand() % 2 || j == cols_ - 1) {
                        bottom_wall_matrix_[i][j] = 1;
                        group_counter++;
                        wall_counter++;
                    } else {
                        group_counter++;
                    }
                }
            } else {
                // Последняя строка
                for (int j = 0; j < cols_; j++) {
                    bottom_wall_matrix_[i][j] = 1;
                    if (j != cols_ - 1) {
                        if (tmp_matrix_[i][j] != tmp_matrix_[i][j + 1]) {
                            int tmp_value = tmp_matrix_[i][j + 1];
                            for (int k = 0; k < cols_; k++) {
                                if (tmp_matrix_[i][k] == tmp_value) {
                                    tmp_matrix_[i][k] = tmp_matrix_[i][j];
                                    right_wall_matrix_[i][j] = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

bool Maze::ParseFile(std::string path) {
    std::fstream fs;
    fs.open(path, std::fstream::in);
    if (!fs.is_open()) return false;
    fs >> rows_;
    fs >> cols_;
    if (!(rows_ >= 2 && rows_ <= 50 && cols_ >= 2 && cols_ <= 50)) {
        rows_ = cols_ = 0;
        return false;
    }
    AllocateMemory();
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            fs >> right_wall_matrix_[i][j];
        }
    }
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            fs >> bottom_wall_matrix_[i][j];
        }
    }

    fs.close();
    return true;
}

std::vector<std::pair<int, int>> Maze::SolveTheMaze(std::pair<int, int> from, std::pair<int, int> to) {
    std::vector<std::pair<int, int>> path;
    path.push_back(from);
    std::pair<int, int> tmp = from;

    RecursiveSearch(from, to, tmp, path);

    return path;
}

void Maze::RecursiveSearch(std::pair<int, int> from, std::pair<int, int> to, std::pair<int, int>& tmp,
                           std::vector<std::pair<int, int>>& path) {
    // доступен проход в верхнюю клетку
    std::vector<std::pair<int, int>>::iterator itr;
    if (path.size() > 1)
        itr = path.end() - 2;
    else
        itr = path.begin();
    if (tmp.first != 0 && !bottom_wall_matrix_[tmp.first - 1][tmp.second] &&
        std::make_pair(tmp.first - 1, tmp.second) != *itr) {
        if (tmp != to) {
            tmp = std::make_pair(tmp.first - 1, tmp.second);
            path.push_back(tmp);
        }
        if (tmp != to) {
            RecursiveSearch(from, to, tmp, path);
        } else {
            return;
        }
    }
    if (tmp == to) return;
    if (tmp == from || *(path.end() - 1) == from) {
        path.clear();
        path.push_back(from);
        itr = path.begin();
    }
    // доступен проход в нижнюю клетку
    if (tmp.first != rows_ - 1 && !bottom_wall_matrix_[tmp.first][tmp.second] &&
        std::make_pair(tmp.first + 1, tmp.second) != *itr) {
        if (tmp != to) {
            tmp = std::make_pair(tmp.first + 1, tmp.second);
            path.push_back(tmp);
        }
        if (tmp != to) {
            RecursiveSearch(from, to, tmp, path);
        } else {
            return;
        }
    }
    if (tmp == to) return;
    if (tmp == from || *(path.end() - 1) == from) {
        path.clear();
        path.push_back(from);
        itr = path.begin();
    }
    // доступен проход в левую клетку
    if (tmp.second != 0 && !right_wall_matrix_[tmp.first][tmp.second - 1] &&
        std::make_pair(tmp.first, tmp.second - 1) != *itr) {
        if (tmp != to) {
            tmp = std::make_pair(tmp.first, tmp.second - 1);
            path.push_back(tmp);
        }
        if (tmp != to) {
            RecursiveSearch(from, to, tmp, path);
        } else {
            return;
        }
    }
    if (tmp == to) return;
    if (tmp == from || *(path.end() - 1) == from) {
        path.clear();
        path.push_back(from);
        itr = path.begin();
    }
    // доступен проход в правую клетку
    if (tmp.second != cols_ - 1 && !right_wall_matrix_[tmp.first][tmp.second] &&
        std::make_pair(tmp.first, tmp.second + 1) != *itr) {
        if (tmp != to) {
            tmp = std::make_pair(tmp.first, tmp.second + 1);
            path.push_back(tmp);
        }
        if (tmp != to) {
            RecursiveSearch(from, to, tmp, path);
        } else {
            return;
        }
    }
    if (tmp == to) return;
    if (tmp == from || *(path.end() - 1) == from) {
        path.clear();
        path.push_back(from);
        itr = path.begin();
    }

    if (path.size() > 1)
        itr = path.end() - 2;
    else
        itr = path.begin();
    tmp = *itr;
    path.pop_back();
}

bool Maze::SaveToTextFile(std::string path) {
    std::fstream fs;
    fs.open(path, std::fstream::out);
    if (!fs.is_open()) {
        return false;
    }
    fs << rows_ << " " << cols_ << std::endl;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            fs << right_wall_matrix_[i][j];
            if (j != cols_ - 1) {
                fs << " ";
            }
        }
        fs << std::endl;
    }
    fs << std::endl;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            fs << bottom_wall_matrix_[i][j];
            if (j != cols_ - 1) {
                fs << " ";
            }
        }
        fs << std::endl;
    }
    fs.close();
    return true;
}

int Maze::GetRows() { return rows_; }
int Maze::GetCols() { return cols_; }
const std::vector<std::vector<int>>& Maze::GetRightWallMatrix() { return right_wall_matrix_; }
const std::vector<std::vector<int>>& Maze::GetBottomWallMatrix() { return bottom_wall_matrix_; }
void Maze::SetRows(int rows) { rows_ = rows; }
void Maze::SetCols(int cols) { cols_ = cols; }
}  // namespace s21
