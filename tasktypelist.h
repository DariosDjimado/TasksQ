#ifndef TASKTYPELIST_H
#define TASKTYPELIST_H
#include <tasktype.h>
#include <QObject>
#include <QStringList>

class TaskTypeList : public QObject
{
    Q_OBJECT
public:
    explicit TaskTypeList(QObject *parent = nullptr);

    bool deleteTaskType(TaskType * taskType);
    int getSize();

    QString getTaskBackgroundColor(QString taskTypeName);

    TaskType * getTaskTypeByPosition(int position);
    TaskType * getTaskTypeByName(QString name);
    TaskType *createTaskType(QString name, QString backgroundColor, QString textColor);


    void addTaskType(TaskType * taskType);



    TaskType *getDefaultTaskType() const;
    void setDefaultTaskType(TaskType *defaultTaskType);

signals:

public slots:


private:
    QList<TaskType *> m_taskTypeList;
    TaskType * m_defaultTaskType;
};

#endif // TASKTYPELIST_H
