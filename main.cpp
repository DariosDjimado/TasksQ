#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    // Types
    TaskTypeList taskTypeList;
    TaskTypeListController taskTypeListController(&taskTypeList);

    // Tasks
    TaskList taskList;
    TaskListController taskListController(&taskList, &taskTypeList);


    MainWindow w(&taskListController, &taskTypeListController);
    w.show();

    return a.exec();
}
