#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <math.h>

#include <QFileDialog>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QMouseEvent>
#include <QWidget>

#include "../Controller/controller.h"
#include "mythread.h"
#include "square.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Threads;

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    Ui::MainWindow* ui;

protected:
    void mousePressEvent(QMouseEvent* event) override;

public slots:
    void on_LoadMazeFromFile_clicked();
    void on_GeneratePerfectMaze_clicked();
    void on_RandomSize_stateChanged(int arg1);
    void on_SolveTheMaze_clicked();
    void on_SaveToTextFile_clicked();
    void on_LoadCaveFromFile_clicked();
    void on_tabWidget_currentChanged();
    void on_generateCave_clicked();
    void on_RandomSizeCave_stateChanged(int arg1);
    void on_nextStep_clicked();
    void on_birthLimit_valueChanged();
    void on_deathLimit_valueChanged();
    void on_autoupdate_clicked();

private:
    void InitScenes();
    void InitPens();
    void PaintMaze();
    void CalculateHeightsAndWidthOfCell();
    void PaintUpperAndLowerBorders();
    void PaintCellsWalls();
    void UserClickedOnMaze();
    void CreateCentresMatrix();
    void FindMinimumDistance();
    void PaintCross();
    void PaintSolution();
    void PaintCave();

    QGraphicsScene* maze_scene_;
    QGraphicsScene* cave_scene_;
    s21::Controller* controller;
    const int field_size_ = 500;
    const int x_shift_ = 6;
    const int y_shift_ = 28;
    int cell_width_, cell_height_;
    const int wall_thickness_ = 2;
    QPen* blackpen;
    QPen* redpen;

    int x_, y_;
    bool on_solve_the_maze_clicked_flag_ = false;
    std::pair<double, double>** centres_ = nullptr;
    int crosses_counter_ = 0;
    std::pair<int, int> nearest_cell_;
    double minimum_distance_;
    std::pair<int, int> from_, to_;

    QString examples_path_;
    MyThread* thread;
signals:
    void SendStop();
private slots:
    void on_fps_valueChanged();
};

#endif  // MAINWINDOW_H
