#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QWidget>
#include <QPaintEvent>
#include <QTime>
#include <QDebug>
#include <QMouseEvent>
#include <QPainterPath>
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
#include <QVBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QTextEdit>
#include <QTextBrowser>
#include <QGroupBox>//模拟方式显示数值
#include <QSpinBox>//数字
#include <QDateEdit>
#include <QTimeEdit>
#include <QDateTimeEdit>
#include <QTabWidget>//不介绍不算控件
#include <QCompleter>
#include <QHBoxLayout>
#include <QDebug>
#include <QPixmap>
#include <QString>
#include <QLCDNumber>
#include <QTabWidget>
#include <QPainter>//执行绘图操作
#include <QBrush>//用于填充
#include <QPicture>
#include <QTime>
#include <QTimer>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>
#include <windows.h>
#include <bits/stdc++.h>
using namespace std;

struct tank{
    //坦克位置及方向的结构体
    int x=42;
    int y=42;
    int direction;//分别用1，2，3，4表示四个不同的方向
};
char ch;//键盘输入的玩家的操作字符
tank player,enemy,enemy2,enemy3;//定义玩家及敌人1，2，3
int xx[5]={0,1,0,-1},yy[5]={1,0,-1,0};//四个方向
bool vis[50][50];//用于bfs算法
int pre[50][50];//用于bfs算法
int bullets[50][50];//通过位运算来表示子弹及其方向
int issleep=0;//用于延迟操作
int mp[50][50]//当前关卡的地图
{
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
    };
int score=3;//生命值
int wintime=-5;//消灭敌人的次数
const int conserve[5][50][50]//三个关卡的地图
{
    {
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,4},
    {4,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,4},
    {4,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,1,1,0,0,0,0,4},
    {4,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,4},
    {4,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,0,1,1,1,0,1,1,0,0,1,1,1,1,0,0,0,0,0,4},
    {4,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,1,0,0,1,1,0,1,1,0,0,0,0,4},
    {4,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,4},
    {4,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0,0,0,1,1,0,0,4},
    {4,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,4},
    {4,2,2,0,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,0,0,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,2,2,4},
    {4,2,2,2,0,0,0,0,0,0,0,0,0,4,4,4,4,4,4,0,0,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,2,2,2,4},
    {4,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,4},
    {4,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,0,0,0,4},
    {4,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,4,4,4,0,0,0,4},
    {4,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,4,4,4,0,0,0,4},
    {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
    {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
    {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
    {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
    {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
    {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
    {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
    {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
    {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
    {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
    {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
    },
    {
        {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
        {4,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,4},
        {4,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,4},
        {4,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,2,2,2,0,0,0,1,1,1,3,3,3,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,2,2,2,0,0,0,1,1,1,3,3,3,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,2,2,2,0,0,0,1,1,1,3,3,3,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,2,2,2,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
        {4,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
        {4,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
        {4,1,0,0,0,0,0,0,0,1,2,2,2,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,4},
        {4,1,1,0,0,0,0,0,1,1,2,2,2,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,4},
        {4,1,1,1,0,0,0,1,1,1,2,2,2,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,4},
        {4,1,1,1,1,0,1,1,1,1,2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
        {4,1,1,1,1,1,1,1,1,1,2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
        {4,1,1,1,1,1,1,1,1,1,2,2,2,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
        {4,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,4,4,4,4,4,4,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,4},
        {4,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,4,4,4,4,4,4,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,4},
        {4,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,4,4,4,4,4,4,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,4},
        {4,1,1,1,1,1,1,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,4},
        {4,1,1,1,1,1,1,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,4},
        {4,1,1,1,1,1,1,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,2,2,2,0,0,0,1,1,1,0,0,0,4},
        {4,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,2,2,2,0,0,0,1,1,1,0,0,0,4},
        {4,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,1,1,1,0,0,0,4},
        {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,1,1,1,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,1,1,1,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,1,1,1,3,3,3,3,3,3,0,0,0,2,2,2,0,0,0,1,1,1,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,1,1,1,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,4},
        {4,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,4},
        {4,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,4},
        {4,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,3,3,3,3,3,3,0,0,0,2,2,2,0,0,0,1,1,1,0,0,0,4},
        {4,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,1,1,1,1,1,1,4},
        {4,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,1,1,1,1,1,1,4},
        {4,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,1,1,1,1,1,1,4},
        {4,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,4},
        {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
        },
    {
        {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
        {4,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,4},
        {4,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,4},
        {4,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,4},
        {4,0,0,0,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,4,4,4,3,3,3,0,0,0,3,3,3,3,3,3,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,4,4,4,3,3,3,0,0,0,3,3,3,3,3,3,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,4,4,4,3,3,3,0,0,0,3,3,3,3,3,3,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,3,3,3,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,3,3,3,0,0,0,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,3,3,3,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,3,3,3,0,0,0,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,3,3,3,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,3,3,3,0,0,0,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,3,3,3,4,4,4,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,4,4,4,3,3,3,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,3,3,3,4,4,4,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,4,4,4,3,3,3,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,3,3,3,4,4,4,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,4,4,4,3,3,3,3,3,3,0,0,0,4},
        {4,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,4},
        {4,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,4},
        {4,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,2,2,2,2,2,2,4,4,4,0,0,0,4,4,4,2,2,2,2,2,2,0,0,0,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,2,2,2,2,2,2,4,4,4,0,0,0,4,4,4,2,2,2,2,2,2,0,0,0,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,2,2,2,2,2,2,4,4,4,0,0,0,4,4,4,2,2,2,2,2,2,0,0,0,3,3,3,0,0,0,4},
        {4,2,2,2,4,4,4,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,4,4,4,2,2,2,4},
        {4,2,2,2,4,4,4,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,4,4,4,2,2,2,4},
        {4,2,2,2,4,4,4,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,4,4,4,2,2,2,4},
        {4,0,0,0,3,3,3,0,0,0,2,2,2,2,2,2,4,4,4,0,0,0,4,4,4,2,2,2,2,2,2,0,0,0,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,2,2,2,2,2,2,4,4,4,0,0,0,4,4,4,2,2,2,2,2,2,0,0,0,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,2,2,2,2,2,2,4,4,4,0,0,0,4,4,4,2,2,2,2,2,2,0,0,0,3,3,3,0,0,0,4},
        {4,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,4},
        {4,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,4},
        {4,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,4},
        {4,0,0,0,3,3,3,3,3,3,4,4,4,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,4,4,4,3,3,3,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,3,3,3,4,4,4,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,4,4,4,3,3,3,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,3,3,3,4,4,4,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,4,4,4,3,3,3,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,3,3,3,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,3,3,3,0,0,0,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,3,3,3,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,3,3,3,0,0,0,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,0,0,0,3,3,3,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,3,3,3,0,0,0,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,4,4,4,3,3,3,0,0,0,3,3,3,3,3,3,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,4,4,4,3,3,3,0,0,0,3,3,3,3,3,3,3,3,3,0,0,0,4},
        {4,0,0,0,3,3,3,3,3,3,3,3,3,0,0,0,3,3,3,4,4,4,3,3,3,0,0,0,3,3,3,3,3,3,3,3,3,0,0,0,4},
        {4,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,4},
        {4,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,4},
        {4,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,4},
        {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
        },
};



MainWindow::MainWindow(QWidget *parent) ://参数初始化表
    QMainWindow(parent),
    ui(new Ui::MainWindow)//新建界面，设置窗口颜色、标题、及大小
{
    //ui 通常指向用这个ui文件bai里面的类创建的实例。
    //就是说通常情况下ui是一个指向这个界面类的指针。而ui->一般就是用来访问这个界面类里面的控件。
    ui->setupUi(this);//类相当于对话框或控件的调色板，它管理着控件或窗体的所有颜色信息，每个窗体或控件都包含一个QPalette对象
    setAutoFillBackground(true);
    QPalette pa = this->palette();
    pa.setBrush(QPalette::Background, QBrush(Qt::black));
    setPalette(pa);
    setWindowTitle("简易版坦克大战");//设置窗口标题
    setFixedSize(1050,850);//设置窗口大小
}


void sleep(int msec)
{
    /*功能描述: 毫秒级非阻塞延时函数
    参数: 延时毫秒数
    其他说明: 已试验,可用,但CPU占用率较高*/
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
void MainWindow::background(){
    QPainter painter(this);
    QPixmap image1;
    image1.load(":/picture/background.png");
    painter.drawPixmap(0,0,820,850,image1);//设置背景图及其大小
}
void MainWindow::paintEvent(QPaintEvent*){
    if(mp[0][0]==6){
        //初始化mp是为了在点击开始按钮前初始背景
        background();
    }else{
    if(score>=0){
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::white);//字体颜色
        ui->label_2->setPalette(pa);
        ui->label_2->setText(QString::fromStdString(to_string(score)));
        }
    else{
        //考虑若分数小于0时屏幕显示负数（这种情况下不会出现）
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::white);
        ui->label_2->setPalette(pa);
        ui->label_2->setText(QString::fromStdString(to_string(0)));
    }
    //重新设置背景为黑色
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    QBrush brush;
    brush.setColor(QColor(0, 0, 0));
    brush.setStyle(Qt::SolidPattern);
    p.setBrush(brush);
    QPen pen=p.pen();
    p.setPen(pen);
    p.drawRect(10, 10, 820, 820 );
    //双重循环更新界面中的地图上每个点的图像
    for(int i=0;i<=40;i++){
        for(int j=0;j<=40;j++){
            if(i==player.x&&j==player.y&&i==enemy.x&&j==enemy.y)//玩家与坦克1相撞
            {
                QPainter painter(this);
                QPixmap pix;
                pix.load("://boom.png");
                painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                player.x=39;
                player.y=13;
                player.direction=1;
                score--;
                if(score>=0){
                    getenemy();
                }
            }
            else if(i==player.x&&j==player.y&&i==enemy2.x&&j==enemy2.y)//玩家与坦克2相撞
            {
                QPainter painter(this);
                QPixmap pix;
                pix.load("://boom.png");
                painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                player.x=39;
                player.y=13;
                player.direction=1;
                score--;
                if(score>=0){
                    getenemy2();
                }
            }
            else if(i==player.x&&j==player.y&&i==enemy3.x&&j==enemy3.y)//玩家与坦克3相撞
            {
                QPainter painter(this);
                QPixmap pix;
                pix.load("://boom.png");
                painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                player.x=39;
                player.y=13;
                player.direction=1;
                score--;
                if(score>=0){
                    getenemy3();
                }
            }
            else if(i==enemy.x&&j==enemy.y&&i==enemy3.x&&j==enemy3.y)//坦克1与坦克3相撞
            {
                QPainter painter(this);
                QPixmap pix;
                pix.load("://boom.png");
                painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                getenemy();
                getenemy3();
            }
            else if(i==enemy.x&&j==enemy.y&&i==enemy2.x&&j==enemy2.y)//坦克1与坦克2相撞
            {
                QPainter painter(this);
                QPixmap pix;
                pix.load("://boom.png");
                painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                getenemy();
                getenemy2();
            }
            else if(i==enemy2.x&&j==enemy2.y&&i==enemy3.x&&j==enemy3.y)//坦克2与坦克3相撞
            {
                QPainter painter(this);
                QPixmap pix;
                pix.load("://boom.png");
                painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                getenemy2();
                getenemy3();
            }
            else if(bullets[i][j]!=0)//若该坐标位置下存在子弹
            {
                if(i==enemy.x&&j==enemy.y)//子弹射击到坦克1
                {
                    bullets[i][j]=0;
                    mp[i][j]=0;
                    enemy.x=50;
                    enemy.y=50;
                    QPainter painter(this);
                    QPixmap pix;
                    pix.load("://boom.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                    painter.fillRect(QRect(11+j*20,11+20*i,18,18), QBrush(Qt::black));
                    wintime++;
                }
                if(i==enemy2.x&&j==enemy2.y)//子弹射击到坦克2
                {
                    bullets[i][j]=0;
                    mp[i][j]=0;
                    enemy2.x=50;
                    enemy2.y=50;
                    QPainter painter(this);
                    QPixmap pix;
                    pix.load("://boom.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                    painter.fillRect(QRect(11+j*20,11+20*i,18,18), QBrush(Qt::black));
                    wintime++;
                }
                if(i==enemy3.x&&j==enemy3.y)//子弹射击到坦克3
                {
                    bullets[i][j]=0;
                    mp[i][j]=0;
                    enemy3.x=50;
                    enemy3.y=50;
                    QPainter painter(this);
                    QPixmap pix;
                    pix.load("://boom.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                    painter.fillRect(QRect(11+j*20,11+20*i,18,18), QBrush(Qt::black));
                    wintime++;
                }
                if(i==player.x&&j==player.y)//子弹射击到玩家
                {
                    bullets[i][j]=0;
                    QPainter painter(this);
                    QPixmap pix;
                    pix.load("://boom.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                    player.x=39;
                    player.y=13;
                    player.direction=1;
                    score--;
                }
                if(mp[i][j]==4)//子弹射击到河流
                {
                    bullets[i][j]=0;
                    QPainter painter(this);
                    QPixmap pix;
                    pix.load(":/picture/water.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
                else if(mp[i][j]==1)//子弹射击到砖块1
                {
                    QPainter painter(this);
                    bullets[i][j]=0;
                    mp[i][j]=0;
                    painter.fillRect(QRect(11+j*20,11+20*i,18,18), QBrush(Qt::black));
                }
                else if(mp[i][j]==2)//子弹射击到砖块2
                {
                    QPainter painter(this);
                    bullets[i][j]=0;
                    mp[i][j]=1;
                    QPixmap pix;
                    pix.load(":/picture/wall1.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
                else if(mp[i][j]==3)//子弹射击到砖块3
                {
                    QPainter painter(this);
                    bullets[i][j]=0;
                    mp[i][j]=2;
                    QPixmap pix;
                    pix.load(":/picture/wall2.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
                else//子弹所处位置没有任何障碍
                {
                    QPainter p(this);
                    brush.setStyle(Qt::SolidPattern);
                    brush.setColor(QColor("#fff"));
                    p.setPen(Qt::NoPen);
                    p.setBrush(brush);
                    p.drawEllipse(QPoint(20+20*j,20+20*i),4,4);

                }
            }
            else if(i==player.x&&j==player.y)//该坐标仅为玩家所处位置（还需判断方向）
            {
                QPainter painter(this);
                QPixmap pix;
                if(player.direction==1){
                    pix.load(":/picture/player1.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
                else if(player.direction==2){
                    pix.load(":/picture/player2.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
                else if(player.direction==3){
                    pix.load(":/picture/player3.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
                else if(player.direction==4){
                    pix.load(":/picture/player4.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
            }
            else if(i==enemy.x&&j==enemy.y)//该坐标仅为坦克1所处位置（还需判断方向）
            {
                QPainter painter(this);
                QPixmap pix;
                if(enemy.direction==1){
                    pix.load(":/picture/enemy1.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
                else if(enemy.direction==2){
                    pix.load(":/picture/enemy2.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
                else if(enemy.direction==3){
                    pix.load(":/picture/enemy3.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
                else if(enemy.direction==4){
                    pix.load(":/picture/enemy4.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
            }
            else if(i==enemy2.x&&j==enemy2.y)//该坐标仅为坦克2所处位置（还需判断方向）
            {
                QPainter painter(this);
                QPixmap pix;
                if(enemy2.direction==1){
                    pix.load(":/picture/enemy1.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
                else if(enemy2.direction==2){
                    pix.load(":/picture/enemy2.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
                else if(enemy2.direction==3){
                    pix.load(":/picture/enemy3.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
                else if(enemy2.direction==4){
                    pix.load(":/picture/enemy4.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
            }
            else if(i==enemy3.x&&j==enemy3.y)//该坐标仅为坦克3所处位置（还需判断方向）
            {
                QPainter painter(this);
                QPixmap pix;
                if(enemy3.direction==1){
                    pix.load(":/picture/enemy1.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
                else if(enemy3.direction==2){
                    pix.load(":/picture/enemy2.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
                else if(enemy3.direction==3){
                    pix.load(":/picture/enemy3.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
                else if(enemy3.direction==4){
                    pix.load(":/picture/enemy4.png");
                    painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
                }
            }
            else if(mp[i][j]==4)//该坐标仅为河流所处位置
            {
                QPainter painter(this);
                QPixmap pix;
                pix.load(":/picture/water.png");
                painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
            }
            else if(mp[i][j]==0)//该坐标无任何物体
            {
                QPainter painter(this);
                painter.fillRect(QRect(11+j*20,11+20*i,18,18), QBrush(Qt::black));
            }
            else if(mp[i][j]==1)//该坐标仅为砖块1所处位置
            {
                QPainter painter(this);
                QPixmap pix;
                pix.load(":/picture/wall1.png");
                painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
            }
            else if(mp[i][j]==2)//该坐标仅为砖块2所处位置
            {
                QPainter painter(this);
                QPixmap pix;
                pix.load(":/picture/wall2.png");
                painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
            }
            else if(mp[i][j]==3)//该坐标仅为砖块3所处位置
            {
                QPainter painter(this);
                QPixmap pix;
                pix.load(":/picture/wall3.png");
                painter.drawPixmap(j*20+10,i*20+10,20,20,pix);
            }
        }
    }
    /*通过位运算更新下次子弹的位置，
      存在的技巧：不同数位上的1表示方向，
      下次子弹的位置之所以*64，
      是为了与如今子弹所处位置区别开来，（前者大于64，后者小于）
      更新后的子弹坐标上的值要远远大于更新前的，
      最后在除以64即可将更新前的子弹值重新设定为0*/
    for(int i=0;i<=40;i++){
        for(int j=0;j<=40;j++){
            if(bullets[i][j]&(1<<1)){
                if(i-1>=1&&i-1<=39){
                    bullets[i-1][j]|=(1<<1)*64;
                }
            }
            if(bullets[i][j]&(1<<2)){
                if(i+1>=1&&i+1<=39)
                    bullets[i+1][j]|=(1<<2)*64;
            }
            if(bullets[i][j]&(1<<3)){
                if(j-1>=1&&j-1<=39)
                    bullets[i][j-1]|=(1<<3)*64;
            }
            if(bullets[i][j]&(1<<4)){
                if(j+1>=1&&j+1<=39)
                    bullets[i][j+1]|=(1<<4)*64;
            }
        }
    }
    for(int i=0;i<=40;i++){
        for(int j=0;j<=40;j++){
            bullets[i][j]/=64;
        }
    }
    }
}

void MainWindow::getenemy()//随机获取坦克1的位置
{
    while(1){
        enemy.x=rand()%38+1;
        enemy.y=rand()%38+1;
        enemy.direction=rand()%4+1;
        if(bullets[enemy.x][enemy.y]!=0)
            continue;
        if(mp[enemy.x][enemy.y]!=0)
            continue;
        if(abs(enemy.x-player.x)<=10)
            continue;
        if(abs(enemy.y-player.y)<=10)
            continue;

        break;
    }
}
void MainWindow::getenemy2()//随机获取坦克2的位置
{
    while(1){
        enemy2.x=rand()%38+1;
        enemy2.y=rand()%38+1;
        enemy2.direction=rand()%4+1;
        if(bullets[enemy2.x][enemy2.y]!=0)
            continue;
        if(mp[enemy2.x][enemy2.y]!=0)
            continue;
        if(abs(enemy2.x-player.x)<=10)
            continue;
        if(abs(enemy2.y-player.y)<=10)
            continue;

        if(abs(enemy2.x-enemy.x)<=5)
            continue;
        if(abs(enemy2.y-enemy.y)<=5)
            continue;


        break;
    }
}
void MainWindow::getenemy3()//随机获取坦克3的位置
{
    while(1){
        enemy3.x=rand()%38+1;
        enemy3.y=rand()%38+1;
        enemy3.direction=rand()%4+1;
        if(bullets[enemy3.x][enemy3.y]!=0)
            continue;
        if(mp[enemy3.x][enemy3.y]!=0)
            continue;
        if(abs(enemy3.x-player.x)<=10)
            continue;
        if(abs(enemy3.y-player.y)<=10)
            continue;

        if(abs(enemy3.x-enemy.x)<=5)
            continue;
        if(abs(enemy3.y-enemy.y)<=5)
            continue;

        if(abs(enemy3.x-enemy2.x)<=5)
            continue;
        if(abs(enemy3.y-enemy2.y)<=5)
            continue;
        break;
    }
}
void MainWindow::tankAI()//坦克1进攻路线
{
    /*首先通过bfs获取坦克可到达的所有位置，
     pre数组记录上一个到达该点的坐标
     */
    memset(vis,0,sizeof(vis));
    memset(pre,0,sizeof(pre));
    queue<pair<int,int> >q;
    while(!q.empty())
        q.pop();
    q.push(pair<int,int>(player.x,player.y));
    vis[player.x][player.y]=1;
    while(!q.empty()){
        pair<int,int> temp=q.front();
        q.pop();

        pair<int,int> nex;
        for(int i=0;i<4;i++){
            nex.first=temp.first+xx[i];
            nex.second=temp.second+yy[i];
            if(nex.first<=0||nex.first>=40||nex.second<=0||nex.second>=40)
                continue;
            if(vis[nex.first][nex.second])
                continue;
            if(mp[nex.first][nex.second]!=0)
                continue;

            vis[nex.first][nex.second]=1;
            pre[nex.first][nex.second]=temp.first*100+temp.second;
            q.push(pair<int,int>(nex.first,nex.second));
        }
    }
    /*
     若坦克1与玩家不能直接到达，则坦克1直接采用在玩家上，下，左，右四个方位
     来进行移动与射击。
     */
    if(pre[enemy.x][enemy.y]==0){
        if(player.x<enemy.x){
            if((enemy.x-1)>1&&mp[enemy.x-1][enemy.y]==0){
                if(enemy.direction==1)
                    enemy.x--;
                else
                    enemy.direction=1;
            }
            else if((enemy.x-1)>1&&mp[enemy.x-1][enemy.y]!=0){
                if(mp[enemy.x-1][enemy.y]==4){
                    getenemy();
                }else{
                if(enemy.direction==1)
                    bullets[enemy.x-1][enemy.y]|=(1<<1);
                else
                    enemy.direction=1;
                }
            }
        }
        else if(player.x>enemy.x){
            if((enemy.x+1)<=39&&mp[enemy.x+1][enemy.y]==0){
                if(enemy.direction==2)
                    enemy.x++;
                else
                    enemy.direction=2;
            }
            else if((enemy.x+1)<=39&&mp[enemy.x+1][enemy.y]!=0){
                if(mp[enemy.x+1][enemy.y]==4){
                    getenemy();
                }else{
                if(enemy.direction==2)
                    bullets[enemy.x+1][enemy.y]|=(1<<2);
                else
                    enemy.direction=2;
                }
            }
        }
        else if(player.y<enemy.y){
            if((enemy.y-1)>1&&mp[enemy.x][enemy.y-1]==0){
                if(enemy.direction==3)
                    enemy.y--;
                else
                    enemy.direction=3;
            }
            else if((enemy.y-1)>1&&mp[enemy.x][enemy.y-1]!=0){
                if(mp[enemy.x][enemy.y-1]==4){
                    getenemy();
                }else{
                if(enemy.direction==3)
                    bullets[enemy.x][enemy.y-1]|=(1<<3);
                else
                    enemy.direction=3;
                }
            }
        }
        else if(player.y>enemy.y){
            if((enemy.y+1)<=39&&mp[enemy.x][enemy.y+1]==0){
                if(enemy.direction==4)
                    enemy.y++;
                else
                    enemy.direction=4;
            }
            else if((enemy.y+1)<=39&&mp[enemy.x][enemy.y+1]!=0){
                if(mp[enemy.x][enemy.y+1]==4){
                    getenemy();
                }else{
                    if(enemy.direction==4)
                        bullets[enemy.x][enemy.y+1]|=(1<<4);
                    else
                        enemy.direction=4;
                }
            }
        }
        return ;
    }
    pair<int,int> temp;
    int ran=rand()%3;//控制难度，以控制敌方坦克是否直接向玩家走来
    //难度最大，坦克1直接根据pre数组向玩家移动
    if(ran==0){
        temp.first=pre[enemy.x][enemy.y]/100;
        temp.second=pre[enemy.x][enemy.y]%100;

        if(enemy.x<temp.first)
            enemy.direction=2;
        else if(enemy.x>temp.first)
            enemy.direction=1;
        else if(enemy.y>temp.second)
            enemy.direction=3;
        else
            enemy.direction=4;
        enemy.x=temp.first;
        enemy.y=temp.second;
    }
    else{
        ran=rand()%3;
        if(ran!=0){
            if(enemy.direction==1&&(enemy.x-1)>1&&mp[enemy.x-1][enemy.y]==0){
                if(enemy.direction==1)
                    enemy.x--;
                else
                    enemy.direction=1;
            }
            else if(enemy.direction==2&&(enemy.x+1)<=39&&mp[enemy.x+1][enemy.y]==0){
                if(enemy.direction==2)
                    enemy.x++;
                else
                    enemy.direction=2;
            }
            else if(enemy.direction==3&&(enemy.y-1)>1&&mp[enemy.x][enemy.y-1]==0){
                if(enemy.direction==3)
                    enemy.y--;
                else
                    enemy.direction=3;
            }
            else if(enemy.direction==4&&(enemy.y+1)<=39&&mp[enemy.x][enemy.y+1]==0){
                if(enemy.direction==4)
                    enemy.y++;
                else
                    enemy.direction=4;
            }
        }
        else{
            ran=rand()%4+1;
            if(ran==1&&(enemy.x-1)>1&&mp[enemy.x-1][enemy.y]==0){
                if(enemy.direction==1)
                    enemy.x--;
                else
                    enemy.direction=1;
            }
            else if(ran==2&&(enemy.x+1)<=39&&mp[enemy.x+1][enemy.y]==0){
                if(enemy.direction==2)
                    enemy.x++;
                else
                    enemy.direction=2;
            }
            else if(ran==3&&(enemy.y-1)>1&&mp[enemy.x][enemy.y-1]==0){
                if(enemy.direction==3)
                    enemy.y--;
                else
                    enemy.direction=3;
            }
            else if(ran==4&&(enemy.y+1)<=39&&mp[enemy.x][enemy.y+1]==0){
                if(enemy.direction==4)
                    enemy.y++;
                else
                    enemy.direction=4;
            }
        }
    }
    //坦克只有在与x或者y坐标相差小于1时才会发起射击
    if(abs(enemy.x-player.x)<=1&&enemy.y>player.y&&ran==0){
        if(enemy.direction!=3)
            enemy.direction=3;
        else{
            bullets[enemy.x][enemy.y-1]|=(1<<3);
        }
    }
    else if(abs(enemy.x-player.x)<=1&&enemy.y<player.y&&ran==0){
        if(enemy.direction!=4)
            enemy.direction=4;
        else{
            bullets[enemy.x][enemy.y+1]|=(1<<4);
        }
    }
    else if(abs(enemy.y-player.y)<=1&&enemy.x>player.x&&ran==0){
        if(enemy.direction!=1)
            enemy.direction=1;
        else{
            bullets[enemy.x-1][enemy.y]|=(1<<1);
        }
    }
    else if(abs(enemy.y-player.y)<=1&&enemy.x<player.x&&ran==0){
        if(enemy.direction!=2)
            enemy.direction=2;
        else{
            bullets[enemy.x+1][enemy.y]|=(1<<2);
        }
    }
}
void MainWindow::tankAI3(){
    memset(vis,0,sizeof(vis));
    memset(pre,0,sizeof(pre));
    queue<pair<int,int> >q;
    //int ans=0;
    while(!q.empty())
        q.pop();
    q.push(pair<int,int>(player.x,player.y));
    vis[player.x][player.y]=1;
    while(!q.empty()){
        pair<int,int> temp=q.front();
        q.pop();

        pair<int,int> nex;
        for(int i=0;i<4;i++){
            nex.first=temp.first+xx[i];
            nex.second=temp.second+yy[i];
            if(nex.first<=0||nex.first>=40||nex.second<=0||nex.second>=40)
                continue;
            if(vis[nex.first][nex.second])
                continue;
            if(mp[nex.first][nex.second]!=0)
                continue;

            vis[nex.first][nex.second]=1;
            pre[nex.first][nex.second]=temp.first*100+temp.second;
            q.push(pair<int,int>(nex.first,nex.second));
        }
    }
    if(pre[enemy3.x][enemy3.y]==0){
        if(player.x<enemy3.x){
            if((enemy3.x-1)>1&&mp[enemy3.x-1][enemy3.y]==0){
                if(enemy3.direction==1)
                    enemy3.x--;
                else
                    enemy3.direction=1;
            }
            else if((enemy3.x-1)>1&&mp[enemy3.x-1][enemy3.y]!=0){
                if(mp[enemy3.x-1][enemy3.y]==4){
                    getenemy3();
                }else{
                if(enemy3.direction==1)
                    bullets[enemy3.x-1][enemy3.y]|=(1<<1);
                else
                    enemy3.direction=1;
                }
            }
        }
        else if(player.x>enemy3.x){
            if((enemy3.x+1)<=39&&mp[enemy3.x+1][enemy3.y]==0){
                if(enemy3.direction==2)
                    enemy3.x++;
                else
                    enemy3.direction=2;
            }
            else if((enemy3.x+1)<=39&&mp[enemy3.x+1][enemy3.y]!=0){
                if(mp[enemy3.x+1][enemy3.y]==4){
                    getenemy3();
                }else{
                if(enemy3.direction==2)
                    bullets[enemy3.x+1][enemy3.y]|=(1<<2);
                else
                    enemy3.direction=2;
                }
            }
        }
        else if(player.y<enemy3.y){
            if((enemy3.y-1)>1&&mp[enemy3.x][enemy3.y-1]==0){
                if(enemy3.direction==3)
                    enemy3.y--;
                else
                    enemy3.direction=3;
            }
            else if((enemy3.y-1)>1&&mp[enemy3.x][enemy3.y-1]!=0){
                if(mp[enemy3.x][enemy3.y-1]==4){
                   getenemy3();
                }else{
                if(enemy3.direction==3)
                    bullets[enemy3.x][enemy3.y-1]|=(1<<3);
                else
                    enemy3.direction=3;
                }
            }
        }
        else if(player.y>enemy3.y){
            if((enemy3.y+1)<=39&&mp[enemy3.x][enemy3.y+1]==0){
                if(enemy3.direction==4)
                    enemy3.y++;
                else
                    enemy3.direction=4;
            }
            else if((enemy3.y+1)<=39&&mp[enemy3.x][enemy3.y+1]!=0){
                if(mp[enemy3.x][enemy3.y+1]==4){
                    getenemy3();
                }else{
                    if(enemy3.direction==4)
                        bullets[enemy3.x][enemy3.y+1]|=(1<<4);
                    else
                        enemy3.direction=4;
                }

            }
        }
        return ;
    }
    pair<int,int> temp;
    int ran=rand()%3;//随机数可通过改变随机数范围来控制难度，以控制敌方坦克是否直接向玩家走来
    if(ran==0){
        temp.first=pre[enemy3.x][enemy3.y]/100;
        temp.second=pre[enemy3.x][enemy3.y]%100;
        if(enemy3.x<temp.first)
            enemy3.direction=2;
        else if(enemy3.x>temp.first)
            enemy3.direction=1;
        else if(enemy3.y>temp.second)
            enemy3.direction=3;
        else
            enemy3.direction=4;
        enemy3.x=temp.first;
        enemy3.y=temp.second;
    }
    else{
        ran=rand()%3;
        if(ran!=0){
            if(enemy3.direction==1&&(enemy3.x-1)>1&&mp[enemy3.x-1][enemy3.y]==0){
                if(enemy3.direction==1)
                    enemy3.x--;
                else
                    enemy3.direction=1;
            }
            else if(enemy3.direction==2&&(enemy3.x+1)<=39&&mp[enemy3.x+1][enemy3.y]==0){
                if(enemy3.direction==2)
                    enemy3.x++;
                else
                    enemy3.direction=2;
            }
            else if(enemy3.direction==3&&(enemy3.y-1)>1&&mp[enemy3.x][enemy3.y-1]==0){
                if(enemy3.direction==3)
                    enemy3.y--;
                else
                    enemy3.direction=3;
            }
            else if(enemy3.direction==4&&(enemy3.y+1)<=39&&mp[enemy3.x][enemy3.y+1]==0){
                if(enemy3.direction==4)
                    enemy3.y++;
                else
                    enemy3.direction=4;
            }
        }
        else{

            ran=rand()%4+1;
            if(ran==1&&(enemy3.x-1)>1&&mp[enemy3.x-1][enemy3.y]==0){
                if(enemy3.direction==1)
                    enemy3.x--;
                else
                    enemy3.direction=1;
            }
            else if(ran==2&&(enemy3.x+1)<=39&&mp[enemy3.x+1][enemy3.y]==0){
                if(enemy3.direction==2)
                    enemy3.x++;
                else
                    enemy3.direction=2;
            }
            else if(ran==3&&(enemy3.y-1)>1&&mp[enemy3.x][enemy3.y-1]==0){
                if(enemy3.direction==3)
                    enemy3.y--;
                else
                    enemy3.direction=3;
            }
            else if(ran==4&&(enemy3.y+1)<=39&&mp[enemy3.x][enemy3.y+1]==0){
                if(enemy3.direction==4)
                    enemy3.y++;
                else
                    enemy3.direction=4;
            }
        }
    }
        if(abs(enemy3.x-player.x)<=1&&enemy3.y>player.y&&ran==0){
            if(enemy3.direction!=3)
                enemy3.direction=3;
            else{
                bullets[enemy3.x][enemy3.y-1]|=(1<<3);
            }
        }
        else if(abs(enemy3.x-player.x)<=1&&enemy3.y<player.y&&ran==0){
            if(enemy3.direction!=4)
                enemy3.direction=4;
            else{
                bullets[enemy3.x][enemy3.y+1]|=(1<<4);
            }
        }
        else if(abs(enemy3.y-player.y)<=1&&enemy3.x>player.x&&ran==0){
            if(enemy3.direction!=1)
                enemy3.direction=1;
            else{
                bullets[enemy3.x-1][enemy3.y]|=(1<<1);
            }
        }
    else if(abs(enemy3.y-player.y)<=1&&enemy3.x<player.x&&ran==0){
        if(enemy3.direction!=2)
            enemy3.direction=2;
        else{
            bullets[enemy3.x+1][enemy3.y]|=(1<<2);
        }
    }
}
void MainWindow::tankAI2(){
    memset(vis,0,sizeof(vis));
    memset(pre,0,sizeof(pre));
    queue<pair<int,int> >q;
    //int ans=0;
    while(!q.empty())
        q.pop();
    q.push(pair<int,int>(player.x,player.y));
    vis[player.x][player.y]=1;
    while(!q.empty()){
        pair<int,int> temp=q.front();
        q.pop();

        pair<int,int> nex;
        for(int i=0;i<4;i++){
            nex.first=temp.first+xx[i];
            nex.second=temp.second+yy[i];
            if(nex.first<=0||nex.first>=40||nex.second<=0||nex.second>=40)
                continue;
            if(vis[nex.first][nex.second])
                continue;
            if(mp[nex.first][nex.second]!=0)
                continue;

            vis[nex.first][nex.second]=1;
            pre[nex.first][nex.second]=temp.first*100+temp.second;
            q.push(pair<int,int>(nex.first,nex.second));
        }
    }
    if(pre[enemy2.x][enemy2.y]==0){
        if(player.x<enemy2.x){
            if((enemy2.x-1)>1&&mp[enemy2.x-1][enemy2.y]==0){
                if(enemy2.direction==1)
                    enemy2.x--;
                else
                    enemy2.direction=1;
            }
            else if((enemy2.x-1)>1&&mp[enemy2.x-1][enemy2.y]!=0){
                if(mp[enemy2.x-1][enemy2.y]==4){
                    getenemy2();
                }else{
                if(enemy2.direction==1)
                    bullets[enemy2.x-1][enemy2.y]|=(1<<1);
                else
                    enemy2.direction=1;
                }
            }
        }
        else if(player.x>enemy2.x){
            if((enemy2.x+1)<=39&&mp[enemy2.x+1][enemy2.y]==0){
                if(enemy2.direction==2)
                    enemy2.x++;
                else
                    enemy2.direction=2;
            }
            else if((enemy2.x+1)<=39&&mp[enemy2.x+1][enemy2.y]!=0){
                if(mp[enemy2.x+1][enemy2.y]==4){
                    getenemy2();
                }else{
                if(enemy2.direction==2)
                    bullets[enemy2.x+1][enemy2.y]|=(1<<2);
                else
                    enemy2.direction=2;
                }
            }
        }
        else if(player.y<enemy2.y){
            if((enemy2.y-1)>1&&mp[enemy2.x][enemy2.y-1]==0){
                if(enemy2.direction==3)
                    enemy2.y--;
                else
                    enemy2.direction=3;
            }
            else if((enemy2.y-1)>1&&mp[enemy2.x][enemy2.y-1]!=0){
                if(mp[enemy2.x][enemy2.y-1]==4){
                    getenemy2();
                }else{
                if(enemy2.direction==3)
                    bullets[enemy2.x][enemy2.y-1]|=(1<<3);
                else
                    enemy2.direction=3;
                }
            }
        }
        else if(player.y>enemy2.y){
            if((enemy2.y+1)<=39&&mp[enemy2.x][enemy2.y+1]==0){
                if(enemy2.direction==4)
                    enemy2.y++;
                else
                    enemy2.direction=4;
            }
            else if((enemy2.y+1)<=39&&mp[enemy2.x][enemy2.y+1]!=0){
                if(mp[enemy2.x][enemy2.y+1]==4){
                    getenemy2();
                }else{
                    if(enemy2.direction==4)
                        bullets[enemy2.x][enemy2.y+1]|=(1<<4);
                    else
                        enemy2.direction=4;
                }

            }
        }
        return ;
    }
    pair<int,int> temp;
    int ran=rand()%3;//随机数可通过改变随机数范围来控制难度，以控制敌方坦克是否直接向玩家走来
    if(ran==0){
        temp.first=pre[enemy2.x][enemy2.y]/100;
        temp.second=pre[enemy2.x][enemy2.y]%100;



        if(enemy2.x<temp.first)
            enemy2.direction=2;
        else if(enemy2.x>temp.first)
            enemy2.direction=1;
        else if(enemy2.y>temp.second)
            enemy2.direction=3;
        else
            enemy2.direction=4;
        enemy2.x=temp.first;
        enemy2.y=temp.second;
    }
    else{
        ran=rand()%3;
        if(ran!=0){
            if(enemy2.direction==1&&(enemy2.x-1)>1&&mp[enemy2.x-1][enemy2.y]==0){
                if(enemy2.direction==1)
                    enemy2.x--;
                else
                    enemy2.direction=1;
            }
            else if(enemy2.direction==2&&(enemy2.x+1)<=39&&mp[enemy2.x+1][enemy2.y]==0){
                if(enemy2.direction==2)
                    enemy2.x++;
                else
                    enemy2.direction=2;
            }
            else if(enemy2.direction==3&&(enemy2.y-1)>1&&mp[enemy2.x][enemy2.y-1]==0){
                if(enemy2.direction==3)
                    enemy2.y--;
                else
                    enemy2.direction=3;
            }
            else if(enemy2.direction==4&&(enemy2.y+1)<=39&&mp[enemy2.x][enemy2.y+1]==0){
                if(enemy2.direction==4)
                    enemy2.y++;
                else
                    enemy2.direction=4;
            }
        }
        else{

            ran=rand()%4+1;
            if(ran==1&&(enemy2.x-1)>1&&mp[enemy2.x-1][enemy2.y]==0){
                if(enemy2.direction==1)
                    enemy2.x--;
                else
                    enemy2.direction=1;
            }
            else if(ran==2&&(enemy2.x+1)<=39&&mp[enemy2.x+1][enemy2.y]==0){
                if(enemy2.direction==2)
                    enemy2.x++;
                else
                    enemy2.direction=2;
            }
            else if(ran==3&&(enemy2.y-1)>1&&mp[enemy2.x][enemy2.y-1]==0){
                if(enemy2.direction==3)
                    enemy2.y--;
                else
                    enemy2.direction=3;
            }
            else if(ran==4&&(enemy2.y+1)<=39&&mp[enemy2.x][enemy2.y+1]==0){
                if(enemy2.direction==4)
                    enemy2.y++;
                else
                    enemy2.direction=4;
            }
        }
    }
        if(abs(enemy2.x-player.x)<=1&&enemy2.y>player.y&&ran==0){
            if(enemy2.direction!=3)
                enemy2.direction=3;
            else{
                bullets[enemy2.x][enemy2.y-1]|=(1<<3);
            }
        }
        else if(abs(enemy2.x-player.x)<=1&&enemy2.y<player.y&&ran==0){
            if(enemy2.direction!=4)
                enemy2.direction=4;
            else{
                bullets[enemy2.x][enemy2.y+1]|=(1<<4);
            }
        }
        else if(abs(enemy2.y-player.y)<=1&&enemy2.x>player.x&&ran==0){
            if(enemy2.direction!=1)
                enemy2.direction=1;
            else{
                bullets[enemy2.x-1][enemy2.y]|=(1<<1);
            }
        }
    else if(abs(enemy2.y-player.y)<=1&&enemy2.x<player.x&&ran==0){
        if(enemy2.direction!=2)
            enemy2.direction=2;
        else{
            bullets[enemy2.x+1][enemy2.y]|=(1<<2);
        }
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::keyPressEvent(QKeyEvent  *event) //声明键盘响应函数
{
    if(event->key() ==Qt::Key_A) {
        ch='a';
    }
    else if(event->key() ==Qt::Key_D){
        ch='d';
    }
    else if(event->key() ==Qt::Key_S) {
        ch='s';
    }
    else if(event->key() == Qt::Key_W){
        ch='w';
    }
    else if(event->key() ==Qt::Key_J){
        ch='j';
    }
}
void MainWindow::mainfunction(){
    memset(bullets,0,sizeof(bullets));//初始化
    //更新地图
    if(ui->comboBox->currentText()=="第一关"){
        for(int i=0;i<=41;i++)
            for(int j=0;j<=41;j++)
                mp[i][j]=conserve[0][i][j];
    }
    else if(ui->comboBox->currentText()=="第二关"){
        for(int i=0;i<=41;i++)
            for(int j=0;j<=41;j++)
                mp[i][j]=conserve[1][i][j];
    }
    else if(ui->comboBox->currentText()=="第三关"){
        for(int i=0;i<=41;i++)
            for(int j=0;j<=41;j++)
                mp[i][j]=conserve[2][i][j];
    }
    //初始化敌方坦克位置
    getenemy();
    getenemy2();
    getenemy3();
    //生命值以及胜利的次数初始化
    score=3;
    wintime=0;
    player.x=39;
    player.y=13;
    player.direction=1;
    sleep(300);
    update();//进入界面更新函数
    while(1){
        //胜利与失败的判断条件
        if(score<=0){
            QMessageBox::about(nullptr, "结束", "你输了");
            this->close();
            return ;
        }
        if(wintime>=3){
            QMessageBox::about(nullptr, "结束", "你赢了");
            return ;
        }
        sleep(300);
        //按键检测后更改玩家方向以及发射子弹
        if(ch=='A'||ch=='a'){
            if(player.y-1>=1&&mp[player.x][player.y-1]==0){
                if(player.direction!=3){
                    player.direction=3;
                }else{
                    player.y--;
                }
            }
            player.direction=3;
            ch='1';
        }
        else if(ch=='S'||ch=='s'){
            if(player.x+1<=39&&mp[player.x+1][player.y]==0){
                if(player.direction!=2){
                    player.direction=2;
                }else{
                    player.x++;
                }
            }
            player.direction=2;
            ch='1';
        }
        else if(ch=='D'||ch=='d'){
            if(player.y+1<=39&&mp[player.x][player.y+1]==0){
                if(player.direction!=4){
                    player.direction=4;
                }else{
                    player.y++;
                }
            }
            player.direction=4;
            ch='1';
        }
        else if(ch=='W'||ch=='w'){
            if(player.x-1>=1&&mp[player.x-1][player.y]==0){
                if(player.direction!=1){
                    player.direction=1;
                }else{
                    player.x--;
                }
            }
            player.direction=1;
            ch='1';
        }
        else if(ch=='J'||ch=='j'){
            if(player.direction==1)
                bullets[player.x-1][player.y]|=(1<<1);
            else if(player.direction==2)
                bullets[player.x+1][player.y]|=(1<<2);
            else if(player.direction==3)
                bullets[player.x][player.y-1]|=(1<<3);
            else if(player.direction==4)
                bullets[player.x][player.y+1]|=(1<<4);
            ch='1';
        }
        tankAI();
        tankAI2();
        tankAI3();
        this->update();
    }
}

void MainWindow::on_pushButton_3_clicked()//开始键，进入游戏界面
{
    mainfunction();
}

void MainWindow::on_pushButton_2_clicked()//暂停键
{
    sleep(1000000);
    issleep=1;
}
