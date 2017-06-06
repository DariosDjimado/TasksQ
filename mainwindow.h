#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "taskListController.h"
#include "tasktypelistcontroller.h"
#include "diagram.h"
#include <QMainWindow>
#include <QHash>

#include <QUndoCommand>
#include <QUndoView>
#include <QTableWidgetItem>


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
    void undo();
    void redo();
    void drawDiagram();

private slots:

private:
    Ui::MainWindow *ui;

    TaskListController * m_controller;
    TaskTypeListController * m_typeController;


    QHash<QTableWidgetItem *, Task *> m_taskMap;
    QHash<TaskType *,int> m_typeMap;

    QUndoStack * m_undoStack;
    QUndoView *undoView;

    Diagram * m_diagram;

    void displayTask(int row, Task * task);
    void setupConnections();
    void setupConfig();
    void init();
    bool config();
};

#endif // MAINWINDOW_H
