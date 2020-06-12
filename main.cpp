#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//用于管理应用程序的资源
    MainWindow w;//定义窗口
    w.show();//将其显示出来
    return a.exec();//a.exec() 启动应用程序的执行，开始应用程序的消息循环和事件处理。
}
