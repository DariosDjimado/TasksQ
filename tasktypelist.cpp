#include "tasktypelist.h"

TaskTypeList::TaskTypeList(QObject *parent) : QObject(parent)
{
    // set the default type
    m_defaultTaskType= new TaskType();
    m_defaultTaskType->setName("Default");

    m_defaultTaskType->setBackgroundColor("red");
    m_defaultTaskType->setTextColor("#fff");
}

bool TaskTypeList::deleteTaskType(TaskType *taskType)
{
    if(m_taskTypeList.contains(taskType)){
        // emit
        m_taskTypeList.removeOne(taskType);
        delete taskType;
        return true;
    }
    return false;
}

int TaskTypeList::getSize()
{
    return m_taskTypeList.size();
}

QString TaskTypeList::getTaskBackgroundColor(QString taskTypeName)
{
    auto taskListSize=m_taskTypeList.size();
    for(int i=0; i<taskListSize; i++){
        if(m_taskTypeList[i]->name()==taskTypeName){
            return m_taskTypeList[i]->backgroundColor();
        }
    }
    return m_defaultTaskType->backgroundColor();
}

TaskType *TaskTypeList::getTaskTypeByPosition(int position)
{
    return m_taskTypeList[position];
}

TaskType *TaskTypeList::getTaskTypeByName(QString name)
{
    bool find=false;
    TaskType *tasktype;
    for(int i=0; i<m_taskTypeList.size();i++){
        if(m_taskTypeList[i]->name()==name){
            tasktype=m_taskTypeList[i];
            find=true;
            break;
        }
    }
    if(find){
        return tasktype;
    }else{
        // if none found then return the default type
        return m_defaultTaskType;
    }
}

TaskType *TaskTypeList::createTaskType(QString name, QString backgroundColor, QString textColor)
{
    auto taskType= new TaskType;
    taskType->setName(name);
    taskType->setTextColor(textColor);
    taskType->setBackgroundColor(backgroundColor);
    return taskType;
}

void TaskTypeList::addTaskType(TaskType * taskType)
{
    m_taskTypeList.append(taskType);
}

TaskType *TaskTypeList::getDefaultTaskType() const
{
    return m_defaultTaskType;
}

void TaskTypeList::setDefaultTaskType(TaskType *defaultTaskType)
{
    m_defaultTaskType = defaultTaskType;
}
