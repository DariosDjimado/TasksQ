#ifndef COMMANDS_H
#define COMMANDS_H
#include "taskListController.h"
#include <QUndoCommand>
#include <QTableWidget>
#include <QHash>

class AddTaskCommand: public QUndoCommand
{
public:
    AddTaskCommand(QTableWidget *table,QHash<int, Task *> *taskMap, TaskListController *taskListController, QUndoCommand *parent=0);
    ~AddTaskCommand();
    void undo() override;
    void redo() override;
private:
    TaskListController * m_taskListController;
    Task * m_task;
    QTableWidget *m_table;
    QHash<int, Task *> * m_taskMap;
    QHash<Task *, int> m_localTaskMap;
    void displayTask(bool isNew, int row, Task *task);
};

#endif // COMMANDS_H
