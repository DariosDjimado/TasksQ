#include "tasktypelistcontroller.h"
#include <QFile>
#include <QTextStream>

TaskTypeListController::TaskTypeListController(TaskTypeList *taskTypeList,
                                               QObject *parent) :
    QObject(parent),
    m_taskTypeList(taskTypeList)
{

}

void TaskTypeListController::loadTaskTypes()
{
    QFile types("TYPES.TASKSQ");
    if(!types.open(QFile::ReadOnly | QFile::Text)){

    }else{

        QTextStream in(&types);
        while(!in.atEnd()){
            auto typeValues=in.readLine().split("|");
            auto taskType=new TaskType;
            taskType->setName(typeValues[0]);
            taskType->setTextColor(typeValues[1]);
            taskType->setBackgroundColor(typeValues[2]);
            m_taskTypeList->addTaskType(taskType);
        }

        types.flush();
        types.close();
    }
}


void TaskTypeListController::saveTaskTypes()
{
    QFile types("TYPES.TASKQ");
    if(!types.open(QFile::WriteOnly | QFile::Text)){

    }else{
        QTextStream out(&types);
        for(int i=0; i<m_taskTypeList->getSize();i++){
            auto taskToSave=m_taskTypeList->getTaskTypeByPosition(i);
            out<<taskToSave->name()<<"|"<<taskToSave->textColor()<<"|"<<taskToSave->backgroundColor()<<endl;
        }

        types.flush();
        types.close();
    }
}

TaskType *TaskTypeListController::getTaskTypeByPosition(int position)
{
    return m_taskTypeList->getTaskTypeByPosition(position);
}

TaskType *TaskTypeListController::getTaskTypeByName(QString name)
{
    return m_taskTypeList->getTaskTypeByName(name);
}

int TaskTypeListController::getSize()
{
    return m_taskTypeList->getSize();
}
