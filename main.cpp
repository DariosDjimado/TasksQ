#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    TaskList taskList;
    TaskListController taskListController(&taskList);
    MainWindow w(&taskListController);
    w.show();

    return a.exec();
}
