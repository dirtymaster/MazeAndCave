#include "mainwindow.h"

#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow) {
    controller = s21::Controller::GetInstance();
    ui->setupUi(this);
    InitScenes();
    InitPens();
    ui->tabWidget->setCurrentWidget(ui->Maze);
    controller->SetMazeOrCave(true);
    thread = MyThread::GetInstance();
    connect(thread, &MyThread::Update, this, &MainWindow::on_nextStep_clicked);
    std::string dir_path = QCoreApplication::applicationDirPath().toStdString();
    examples_path_ = QString::fromStdString(dir_path.replace(dir_path.size() - 3, 3, "") + "examples/");
//    dir_path = "/Users/pilafber/Desktop/Projects/MazeGithub/";                 // для билда в qt
//    examples_path_ = "/Users/pilafber/Desktop/Projects/MazeGithub/examples/";  // для билда в qt
}

void MainWindow::InitScenes() {
    maze_scene_ = new QGraphicsScene();
    maze_scene_->setSceneRect(-(field_size_ / 2), -(field_size_ / 2), field_size_, field_size_);
    ui->graphicsView->setScene(maze_scene_);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    cave_scene_ = new QGraphicsScene();
    cave_scene_->setSceneRect(-(field_size_ / 2), -(field_size_ / 2), field_size_, field_size_);
    ui->graphicsView_cave->setScene(cave_scene_);
    ui->graphicsView_cave->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_cave->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWindow::InitPens() {
    blackpen = new QPen(Qt::black);
    blackpen->setWidth(2);
    redpen = new QPen(Qt::red);
    redpen->setWidth(2);
}

MainWindow::~MainWindow() {
    delete ui;
    delete maze_scene_;
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
}

void MainWindow::on_LoadMazeFromFile_clicked() {
    controller->ClearData();
    thread->Stop();
    controller->SetMazeOrCave(true);
    QString str;
    str = QFileDialog::getOpenFileName(this, "Выберите файл", examples_path_, "text files (*.txt)");
    bool success = true;
    if (str.size() != 0) {
        success = controller->ParseFile(str.toStdString());
        if (success) {
            PaintMaze();
        }
    } else {
        success = false;
    }

    if (!success) {
        QMessageBox::about(this, "Ошибка", "Некорректный файл.");
    }
}

void MainWindow::on_GeneratePerfectMaze_clicked() {
    controller->ClearData();
    thread->Stop();
    controller->SetMazeOrCave(true);
    if (ui->RandomSize->isChecked()) {
        controller->SetRandomSize();
    } else {
        controller->SetRows(ui->HeightSpinBox->value());
        controller->SetCols(ui->WidthSpinBox->value());
    }
    controller->GeneratePerfect();
    PaintMaze();
}

void MainWindow::PaintMaze() {
    maze_scene_->clear();
    crosses_counter_ = 0;

    CalculateHeightsAndWidthOfCell();
    PaintUpperAndLowerBorders();
    PaintCellsWalls();

    ui->SolveTheMaze->setEnabled(true);
    ui->SaveToTextFile->setEnabled(true);
}

void MainWindow::CalculateHeightsAndWidthOfCell() {
    cell_height_ = ((field_size_ - wall_thickness_ * 3) - (controller->GetRows() - 1) * wall_thickness_) /
                   controller->GetRows();
    cell_width_ = ((field_size_ - wall_thickness_ * 3) - (controller->GetCols() - 1) * wall_thickness_) /
                  controller->GetCols();
}

void MainWindow::PaintUpperAndLowerBorders() {
    maze_scene_->addLine(
        -(field_size_ / 2 - wall_thickness_), -(field_size_ / 2 - wall_thickness_),
        -(field_size_ / 2 - wall_thickness_) + (cell_width_ + wall_thickness_) * controller->GetCols(),
        -(field_size_ / 2 - wall_thickness_), *blackpen);
    maze_scene_->addLine(-(field_size_ / 2 - wall_thickness_), -(field_size_ / 2 - wall_thickness_),
                         -(field_size_ / 2 - wall_thickness_),
                         -(field_size_ / 2 - wall_thickness_) + (cell_height_ + 2) * controller->GetRows(),
                         *blackpen);
}

void MainWindow::PaintCellsWalls() {
    for (int i = 0; i < controller->GetRows(); i++) {
        for (int j = 0; j < controller->GetCols(); j++) {
            if (controller->GetRightWallMatrix()[i][j] == 1) {
                int x_ = -(field_size_ / 2 - wall_thickness_) + (cell_width_ + wall_thickness_) * (j + 1);
                maze_scene_->addLine(
                    x_, -(field_size_ / 2 - wall_thickness_) + (cell_height_ + wall_thickness_) * i, x_,
                    -(field_size_ / 2 - wall_thickness_) + (cell_height_ + wall_thickness_) * (i + 1),
                    *blackpen);
            }
            if (controller->GetBottomWallMatrix()[i][j] == 1) {
                int y_ = -(field_size_ / 2 - wall_thickness_) + (cell_height_ + wall_thickness_) * (i + 1);
                maze_scene_->addLine(
                    -(field_size_ / 2 - wall_thickness_) + (cell_width_ + wall_thickness_) * j, y_,
                    -(field_size_ / 2 - wall_thickness_) + (cell_width_ + wall_thickness_) * (j + 1), y_,
                    *blackpen);
            }
        }
    }
}

void MainWindow::on_RandomSize_stateChanged(int arg1) {
    if (arg1 == Qt::Checked) {
        ui->HeightSpinBox->setEnabled(false);
        ui->WidthSpinBox->setEnabled(false);
    } else {
        ui->HeightSpinBox->setEnabled(true);
        ui->WidthSpinBox->setEnabled(true);
    }
}

void MainWindow::on_SaveToTextFile_clicked() {
    QString str;
    str = QFileDialog::getOpenFileName(this, "Выберите файл", examples_path_, "text files (*.txt)");
    bool success = true;
    if (str.size() != 0) {
        success = controller->SaveToTextFile(str.toStdString());
    } else {
        success = false;
    }
    if (success) {
        QMessageBox::about(this, "", "Файл сохранен.");
    } else {
        QMessageBox::about(this, "Ошибка", "Некорректный файл.");
    }
}

void MainWindow::on_SolveTheMaze_clicked() {
    on_solve_the_maze_clicked_flag_ = true;
    ui->SolveTheMaze->setEnabled(false);
    QMessageBox::about(this, "", "Пожалуйста, выберите 2 точки лабиринта");
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (on_solve_the_maze_clicked_flag_) {
        // Получаем координаты клика
        QWidget::mousePressEvent(event);
        x_ = event->x();
        y_ = event->y();

        UserClickedOnMaze();
    }
}

void MainWindow::UserClickedOnMaze() {
    if (x_ >= x_shift_ && x_ <= x_shift_ + 500 && y_ >= y_shift_ && y_ <= y_shift_ + 500) {
        if (crosses_counter_ < 2) {
            minimum_distance_ = field_size_;
            if (!centres_) {
                CreateCentresMatrix();
            }
            FindMinimumDistance();

            if (from_ != to_) {
                PaintCross();
            }
        }
    }
}

void MainWindow::CreateCentresMatrix() {
    centres_ = new std::pair<double, double> *[controller->GetRows()];
    for (int i = 0; i < controller->GetRows(); i++) {
        centres_[i] = new std::pair<double, double>[controller->GetCols()];
        for (int j = 0; j < controller->GetCols(); j++) {
            centres_[i][j].first =
                wall_thickness_ + (cell_width_ + wall_thickness_) * j + cell_width_ / 2 + x_shift_;  // x_
            centres_[i][j].second =
                wall_thickness_ + (cell_height_ + wall_thickness_) * i + cell_height_ / 2 + y_shift_;  // y_
        }
    }
}

void MainWindow::FindMinimumDistance() {
    for (int i = 0; i < controller->GetRows(); i++) {
        for (int j = 0; j < controller->GetCols(); j++) {
            int leg1, leg2;
            if (y_ < centres_[i][j].second) {
                leg1 = y_ - centres_[i][j].second;
            } else {
                leg1 = centres_[i][j].second - y_;
            }
            if (x_ < centres_[i][j].first) {
                leg2 = centres_[i][j].first - x_;
            } else {
                leg2 = x_ - centres_[i][j].first;
            }
            double distance = sqrt(leg1 * leg1 + leg2 * leg2);

            if (distance < minimum_distance_) {
                minimum_distance_ = distance;
                nearest_cell_ = std::make_pair(j, i);
                if (crosses_counter_ == 1) {
                    to_ = std::make_pair(i, j);
                } else {
                    from_ = std::make_pair(i, j);
                }
            }
        }
    }
}

void MainWindow::PaintCross() {
    QPolygon pol1, pol2;
    pol1 << QPoint(
                -(field_size_ / 2) + wall_thickness_ + (cell_width_ + wall_thickness_) * nearest_cell_.first,
                -(field_size_ / 2) + wall_thickness_ +
                    (cell_height_ + wall_thickness_) * nearest_cell_.second)
         << QPoint(-(field_size_ / 2) + wall_thickness_ +
                       (cell_width_ + wall_thickness_) * nearest_cell_.first + cell_width_,
                   -(field_size_ / 2) + wall_thickness_ +
                       (cell_height_ + wall_thickness_) * nearest_cell_.second + cell_height_);
    pol2 << QPoint(-(field_size_ / 2) + wall_thickness_ +
                       (cell_width_ + wall_thickness_) * nearest_cell_.first + cell_width_,
                   -(field_size_ / 2) + wall_thickness_ +
                       (cell_height_ + wall_thickness_) * nearest_cell_.second)
         << QPoint(
                -(field_size_ / 2) + wall_thickness_ + (cell_width_ + wall_thickness_) * nearest_cell_.first,
                -(field_size_ / 2) + wall_thickness_ +
                    (cell_height_ + wall_thickness_) * nearest_cell_.second + cell_height_);

    maze_scene_->addPolygon(pol1, *redpen);
    maze_scene_->addPolygon(pol2, *redpen);
    crosses_counter_++;

    if (crosses_counter_ == 2) {
        PaintSolution();
    }
}

void MainWindow::PaintSolution() {
    for (int i = 0; i < controller->GetRows(); i++) {
        delete[] centres_[i];
    }
    delete[] centres_;
    centres_ = nullptr;

    std::vector<std::pair<int, int>> path = controller->SolveTheMaze(from_, to_);

    for (unsigned long int i = 0; i < path.size() - 1; i++) {
        QPolygon pol;
        pol << QPoint(-(field_size_ / 2) + wall_thickness_ +
                          (cell_width_ + wall_thickness_) * path[i].second + cell_width_ / 2,
                      -(field_size_ / 2) + wall_thickness_ +
                          (cell_height_ + wall_thickness_) * path[i].first + cell_height_ / 2)
            << QPoint(-(field_size_ / 2) + wall_thickness_ +
                          (cell_width_ + wall_thickness_) * path[i + 1].second + cell_width_ / 2,
                      -(field_size_ / 2) + wall_thickness_ +
                          (cell_height_ + wall_thickness_) * path[i + 1].first + cell_height_ / 2);
        maze_scene_->addPolygon(pol, *redpen);
    }

    on_solve_the_maze_clicked_flag_ = false;
}

void MainWindow::on_LoadCaveFromFile_clicked() {
    thread->Stop();
    controller->ClearData();
    controller->SetMazeOrCave(false);
    QString str;
    str = QFileDialog::getOpenFileName(this, "Выберите файл", examples_path_, "text files (*.txt)");
    bool success = true;
    if (str.size() != 0) {
        success = controller->ParseFile(str.toStdString());
        if (success) {
            PaintCave();
        }
    } else {
        success = false;
    }

    if (!success) {
        QMessageBox::about(this, "Ошибка", "Некорректный файл.");
    }
    ui->birthLimit->setEnabled(true);
    ui->deathLimit->setEnabled(true);
    ui->nextStep->setEnabled(true);
    ui->fps->setEnabled(true);
    ui->autoupdate->setEnabled(true);
}

void MainWindow::on_generateCave_clicked() {
    thread->Stop();
    controller->ClearData();
    controller->SetMazeOrCave(false);
    if (ui->RandomSizeCave->isChecked()) {
        controller->SetRandomSize();
    } else {
        controller->SetRows(ui->WidthSpinBoxCave->value());
        controller->SetCols(ui->WidthSpinBoxCave->value());
    }
    controller->GeneratePerfect();
    PaintCave();
    ui->birthLimit->setEnabled(true);
    ui->deathLimit->setEnabled(true);
    ui->nextStep->setEnabled(true);
    ui->fps->setEnabled(true);
    ui->autoupdate->setEnabled(true);
}

void MainWindow::on_RandomSizeCave_stateChanged(int arg1) {
    if (arg1 == Qt::Checked) {
        ui->WidthSpinBoxCave->setEnabled(false);
    } else {
        ui->WidthSpinBoxCave->setEnabled(true);
    }
}

void MainWindow::PaintCave() {
    cave_scene_->clear();

    cell_height_ = cell_width_ =
        (field_size_ - (field_size_ % controller->GetRows())) / controller->GetRows();

    for (int i = 0; i < controller->GetRows(); ++i) {
        for (int j = 0; j < controller->GetCols(); ++j) {
            if (controller->GetCaveMatrix()[i][j]) {
                Square *square = new Square(i, j, field_size_, cell_height_, cell_width_);
                cave_scene_->addItem(square);
            }
        }
    }
}

void MainWindow::on_tabWidget_currentChanged() {}

void MainWindow::on_nextStep_clicked() {
    controller->NextStep(ui->birthLimit->value(), ui->deathLimit->value());
    PaintCave();
}

void MainWindow::on_birthLimit_valueChanged() {
    if (ui->birthLimit->value() <= ui->deathLimit->value())
        ui->deathLimit->setValue(ui->birthLimit->value() - 1);
}

void MainWindow::on_deathLimit_valueChanged() {
    if (ui->deathLimit->value() + 1 >= ui->birthLimit->value())
        ui->birthLimit->setValue(ui->deathLimit->value() + 1);
}

void MainWindow::on_autoupdate_clicked() {
    thread->ChangeFps(ui->fps->value());
    thread->GetInstance()->start();
}

void MainWindow::on_fps_valueChanged() { thread->ChangeFps(ui->fps->value()); }
