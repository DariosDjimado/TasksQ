#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "taskListController.h"

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
    explicit MainWindow(TaskListController * controller, QWidget *parent = 0);
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



    QHash<int, Task *> m_taskMap;


    enum {
        NAME, START_DATE,START_TIME, END_DATE, END_TIME, TYPE, COMMENT
    };



    void setupConnections();
    void setupConfig();
    void init();

    void displayTask(int row, Task * task);
};

#endif // MAINWINDOW_H
