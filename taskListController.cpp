#include "taskListController.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>


TaskListController::TaskListController(
        TaskList *taskList,TaskTypeList * taskTypeList, QObject *parent) :
    QObject(parent),
    m_taskList(taskList),
    m_taskTypeList(taskTypeList)
{
    Q_ASSERT(taskList!=nullptr);
    Q_ASSERT(taskTypeList!=nullptr);
}

Task *TaskListController::createTask()
{
    auto task= m_taskList->createTask();
    if(task!=nullptr){
        task->setName(tr("New task..."));
        task->setStartDate(QDate().currentDate());
        task->setEndDate(QDate().currentDate());
        task->setStartTime(QTime().currentTime());
        task->setEndTime(QTime().currentTime());

        task->setType(m_taskTypeList->getDefaultTaskType());


        task->setComment(tr("No comment..."));
        task->setSaved(false);
    }
    return task;
}

bool TaskListController::deleteTask(Task *task)
{
    return m_taskList->deleteTask(task);
}

QList<Task *> TaskListController::selectByStartDate(QDate startDate)
{
    return m_taskList->selectTasksByStartDate(startDate);
}

bool TaskListController::saveTasks()
{
    QFile data("tasks.json");
    if(!data.open(QIODevice::WriteOnly)){
        logs(QDate().currentDate().toString("dd.MM.yyyy")+": cannot save data");
        return false;
    }else{

        QJsonArray dataToSave;

        auto taskList=m_taskList->taskList();
        //if(currentaTask->saved()==true){
        for(int i=0; i<taskList.size();i++)
        {
            auto currentaTask=taskList[i];

            dataToSave.append({
                                  QJsonValue({
                                                 {"task_name",currentaTask->name()},
                                                 {"start_date", currentaTask->startDate().toString("dd.MM.yyyy")},
                                                 {"end_date", currentaTask->endDate().toString("dd.MM.yyyy")},

                                                 {"start_time", currentaTask->startTime().toString()},
                                                 {"end_time", currentaTask->endTime().toString()},

                                                 {"type", currentaTask->type()->name()},
                                                 {"comment", currentaTask->comment()}
                                             })
                              });

        }

     data.write(QJsonDocument(dataToSave).toJson());

    return true;

    }
}

bool TaskListController::loadTasks()
{
    QFile data("tasks.json");

    if(!data.open(QFile::ReadOnly)){
        logs(QDate().currentDate().toString("dd.MM.yyyy")+": cannot load data");
        return false;
    }else{

        QByteArray dataLoad=data.readAll();
        QJsonDocument loadTasks(QJsonDocument::fromJson(dataLoad));
        QJsonArray taskObject=loadTasks.array();

        for(QJsonArray::Iterator it=taskObject.begin(); it!=taskObject.end();it++){
            QJsonObject taskValues=it->toObject();

            // create taskType
           auto loadedTask=m_taskList->createTask();

            loadedTask->setName(taskValues["task_name"].toString());
            loadedTask->setStartDate(QDate::fromString(taskValues.take("start_date").toString(),"dd.MM.yyyy"));
            loadedTask->setEndDate(QDate::fromString(taskValues.take("end_date").toString(),"dd.MM.yyyy"));


            loadedTask->setStartTime(QTime::fromString(taskValues.take("start_time").toString()));
            loadedTask->setEndTime(QTime::fromString(taskValues.take("end_time").toString()));

            loadedTask->setComment(taskValues.take("comment").toString());

            loadedTask->setType(m_taskTypeList->getTaskTypeByName(taskValues.take("type").toString()));
        }
        return true;
    }
}

void TaskListController::logs(QString error)
{
    auto date=QDate().currentDate().toString("dd-MM-yyyy");

    QFile logFile("logFile-"+date);
    if(!logFile.open(QFile::WriteOnly | QFile::Text)){

    } else{
        QTextStream out(&logFile);
        out<<error<<endl;

        logFile.flush();
        logFile.close();
    }

}

int TaskListController::getSize()
{
    return m_taskList->getSize();
}

Task *TaskListController::getTask(int position)
{
    return m_taskList->getTask(position);
}
