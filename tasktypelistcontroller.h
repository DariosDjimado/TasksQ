#ifndef TASKTYPELISTCONTROLLER_H
#define TASKTYPELISTCONTROLLER_H

#include "tasktypelist.h"
#include <QObject>

class TaskTypeListController : public QObject
{
    Q_OBJECT
public:
    explicit TaskTypeListController(TaskTypeList * taskTypeList, QObject *parent = nullptr);
    void loadTaskTypes();
    void saveTaskTypes();
    TaskType * getTaskTypeByPosition(int position);
    TaskType * getTaskTypeByName(QString name);
    int getSize();

signals:

public slots:
private:
    TaskTypeList * m_taskTypeList;
};

#endif // TASKTYPELISTCONTROLLER_H
