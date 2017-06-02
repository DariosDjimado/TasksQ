#include "reset.h"
#include <QFile>
#include <QTextStream>
#include "task.h"

Reset::Reset(QObject *parent) : QObject(parent)
{

}

void Reset::doReset()
{
    resetTypes();
    resetTasks();
}

void Reset::resetTypes()
{
    QFile types("TYPES.TASKSQ");
    if(!types.open(QFile::WriteOnly | QFile::Text)){

    }else{
        QTextStream out(&types);
        // default
        out<<tr("Default")<<"|"<<"#fff"<<"|"<<"red"<<endl;

        // Birthday
        out<<tr("Birthday")<<"|"<<"#fff"<<"|"<<"#FF9800"<<endl;

        // Sport
        out<<tr("Sport")<<"|"<<"#fff"<<"|"<<"#607D8B"<<endl;

        types.flush();
        types.close();
    }
}

void Reset::resetTasks()
{
    QFile db("DATA.TASKSQ");

    if(!db.open(QFile::WriteOnly | QFile::Text)){


    }else{
        QTextStream outt(&db);
        // first run
        auto firstRunTask=new Task;
        firstRunTask->setName("Prise en main");
        firstRunTask->setStartDate(QDate().currentDate());
        firstRunTask->setEndDate(QDate().currentDate());
        firstRunTask->setStartTime(QTime().currentTime());
        firstRunTask->setEndTime(QTime().currentTime().addSecs(300));
        firstRunTask->setComment("Feel free to use this amazing software");


        // TODO save the first run task

        db.flush();
        db.close();
    }
}

