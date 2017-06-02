#ifndef TASKCONTROLLER_H
#define TASKCONTROLLER_H
#include "tasklist.h"
#include "tasktypelist.h"
#include <QObject>

class TaskListController : public QObject
{
    Q_OBJECT
public:
    explicit TaskListController(TaskList * taskList,TaskTypeList * taskTypeList, QObject *parent = nullptr);
    Task * createTask();
    bool deleteTask(Task* task);

    QList<Task *> selectByStartDate(QDate startDate);

    bool saveTasks();
    bool loadTasks();
    void logs(QString error);
    int getSize();

    Task * getTask(int position);


signals:

public slots:

private:
    TaskList * m_taskList;
    TaskTypeList * m_taskTypeList;

};

#endif // TASKCONTROLLER_H
