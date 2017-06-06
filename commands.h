#ifndef COMMANDS_H
#define COMMANDS_H
#include "taskListController.h"
#include <QUndoCommand>
#include <QTableWidget>
#include <QHash>

class BaseCommand:public QUndoCommand
{
public:
    BaseCommand(QTableWidget *table,QHash<QTableWidgetItem *, Task *> *taskMap, TaskListController *taskListController, QUndoCommand *parent=0);

protected:
    QTableWidget *m_table;
    QHash<QTableWidgetItem *, Task *> * m_taskMap;
    TaskListController * m_taskListController;
    void displayTask(int row, Task *task);
};

class AddTaskCommand: public BaseCommand
{
public:
    AddTaskCommand(QTableWidget *table,QHash<QTableWidgetItem *, Task *> *taskMap, TaskListController *taskListController, QUndoCommand *parent=0);
    ~AddTaskCommand();
    void undo() override;
    void redo() override;
private:
    Task * m_task;
    QHash<Task *, QTableWidgetItem *> m_localTaskMap;
};


class DeleteCommand: public BaseCommand
{
public:
    DeleteCommand(QTableWidget *table,QHash<QTableWidgetItem *, Task *> *taskMap, TaskListController *taskListController, QUndoCommand *parent=0);
    ~DeleteCommand();
    void undo() override;
    void redo() override;


private:
    Task * m_task;
    int m_row;

};

#endif // COMMANDS_H
