#include "tasktypelistcontroller.h"
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

TaskTypeListController::TaskTypeListController(TaskTypeList *taskTypeList,
                                               QObject *parent) :
    QObject(parent),
    m_taskTypeList(taskTypeList)
{

}

bool TaskTypeListController::loadTaskTypes()
{

    QFile typesFile("types.json");
    if(!typesFile.open(QIODevice::ReadOnly)){
        // TODO openning error
        return false;
    }


    QByteArray data=typesFile.readAll();
    QJsonDocument loadTypes(QJsonDocument::fromJson(data));
    QJsonArray typesObject=loadTypes.array();

    for(QJsonArray::Iterator it=typesObject.begin(); it!=typesObject.end();it++){
        QJsonObject type=it->toObject();

        // create taskType
        auto taskType=new TaskType;


        QString name=type.take("name").toString();
        taskType->setName(name);
        taskType->setTextColor(type.take("text_color").toString());
        taskType->setBackgroundColor(type.take("background_color").toString());

        if(name=="default"){
            m_taskTypeList->setDefaultTaskType(taskType);
        }

        m_taskTypeList->addTaskType(taskType);
    }
    return true;
}


bool TaskTypeListController::saveTaskTypes()
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

    return true;
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
