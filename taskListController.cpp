#include "taskListController.h"
#include <QFile>
#include <QTextStream>

#include <iostream>
using namespace std;

TaskListController::TaskListController(
        TaskList *taskList, QObject *parent) :
    QObject(parent),
  m_taskList(taskList)
{
    Q_ASSERT(taskList!=nullptr);
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
        task->setType(0);
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

bool TaskListController::saveData()
{
    QFile db("DATA.TASKQ");
    if(!db.open(QFile::WriteOnly | QFile::Text)){
        logs(QDate().currentDate().toString("dd.MM.yyyy")+": cannot save data");
        return false;
    }else{
        auto taskList=m_taskList->taskList();
        QTextStream out(&db);
        for(int i=0; i<taskList.size();i++){
            auto currentaTask=taskList[i];
            if(currentaTask->saved()==true){
                out << currentaTask->name()<<"|";
                out << currentaTask->startDate().toString("dd.MM.yyyy")<<"|";
                out << currentaTask->startTime().toString("hh.mm.ss")<<"|";
                out <<currentaTask->endDate().toString("dd.MM.yyyy")<<"|";
                out <<currentaTask->endTime().toString("hh.mm.ss")<<"|";
                out <<currentaTask->type()<<"|";
                out<<currentaTask->comment()<<endl;
            }
        }
        db.flush();
        db.close();
        return true;
    }

}

bool TaskListController::loadData()
{
    QFile db("DATA.TASKQ");

    if(!db.open(QFile::ReadOnly | QFile::Text)){
        logs(QDate().currentDate().toString("dd.MM.yyyy")+": cannot load data");
        return false;
    }else{
        QTextStream in(&db);
        while(!in.atEnd()){
            auto line=in.readLine();
            auto listLine=line.split("|");

            auto loadedTask=m_taskList->createTask();

            loadedTask->setName(listLine[0]);
            loadedTask->setStartDate(QDate::fromString(listLine[1],"dd.MM.yyyy"));
            loadedTask->setStartTime(QTime::fromString(listLine[2],"hh.mm.ss"));
            loadedTask->setEndDate(QDate::fromString(listLine[3],"dd.MM.yyyy"));
            loadedTask->setEndTime(QTime::fromString(listLine[4],"hh.mm.ss"));
            loadedTask->setType(listLine[5].toInt());
            loadedTask->setComment(listLine[6]);
            loadedTask->setSaved(true);


        }
        db.flush();
        db.close();
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

