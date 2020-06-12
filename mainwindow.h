#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QPaintEvent>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QBrush>
#include <QMessageBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPalette>
#include <QtDebug>
#include <QPushButton>
#include <QLabel>
#include <QMainWindow>
#include <bits/stdc++.h>
using namespace std;
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void background();
    void getenemy();
    void getenemy2();
    void getenemy3();
    void tankAI();
    void tankAI2();
    void tankAI3();
    void mainfunction();
    void keyPressEvent(QKeyEvent  *event);
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QButtonGroup *SelectModeGroup;
};

#endif // MAINWINDOW_H
