#ifndef TASKLIST_H
#define TASKLIST_H

#include "task.h"
#include <QObject>
#include <QList>

class TaskList : public QObject
{
    Q_OBJECT
public:
    explicit TaskList(QObject *parent = 0);

    QList<Task *> taskList() const;
    Task * createTask();
    bool deleteTask(Task *task);


    QList<Task *> selectTasksByStartDate(QDate startDate);
    int getSize();
    Task * getTask(int position);

signals:
    void taskAdded();
    void taskRemoved();

public slots:

private:
   QList<Task *> m_taskList;
};

#endif // TASKLIST_H
