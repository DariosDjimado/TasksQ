#include "tasklist.h"

TaskList::TaskList(QObject *parent) : QObject(parent)
{

}

QList<Task *> TaskList::taskList() const
{
    return m_taskList;
}

Task *TaskList::createTask()
{
    auto task = new Task(this);

    if(task!=nullptr){
        m_taskList.append(task);
        emit taskAdded();
    }
    return task;
}

bool TaskList::deleteTask(Task *task)
{
    if(m_taskList.contains(task)){
        emit taskRemoved();
        m_taskList.removeOne(task);
        delete task;
        return true;
    }

    return false;
}

QList<Task *> TaskList::selectTasksByStartDate(QDate startDate)
{
    QList<Task *> result;
    for (int i=0; i<m_taskList.size();i++){
        if(m_taskList[i]->startDate()==startDate){
            result.append(m_taskList[i]);
        }
    }
    return result;
}

int TaskList::getSize()
{
    return m_taskList.size();
}

Task *TaskList::getTask(int position)
{
    auto result=m_taskList[position];
    return result;
}

