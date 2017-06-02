#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "taskListController.h"
#include "tasktypelistcontroller.h"

#include <QMainWindow>
#include <QHash>


namespace Ui {
class MainWindow;
}
class QListWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(TaskListController * controller,TaskTypeListController * taskController, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void createTask();
    void deleteTask();
    void editTask();
    void saveTask();
    void discardTask();

private slots:


private:
    Ui::MainWindow *ui;

    TaskListController * m_controller;
    TaskTypeListController * m_typeController;


    QHash<int, Task *> m_taskMap;
    QHash<TaskType *,int> m_typeMap;


    enum {
        NAME, START_DATE,START_TIME, END_DATE, END_TIME, TYPE, COMMENT
    };



    void setupConnections();
    void setupConfig();
    void init();

    void displayTask(bool isNew,int row, Task * task);
};

#endif // MAINWINDOW_H
