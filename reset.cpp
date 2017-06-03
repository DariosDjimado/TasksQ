#include "reset.h"
#include "task.h"
#include "tasktypelist.h"

#include <QFile>
#include <QTextStream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

Reset::Reset(QObject *parent) : QObject(parent)
{

}

bool Reset::doReset()
{
    return resetTypes() && resetTasks();

}

bool Reset::resetTypes()
{
    QFile typesFile("types.json");
    if(!typesFile.open(QIODevice::WriteOnly)){
        // TODO handle openning error
        return false;
    }

    QJsonArray typesColorMap
    {

         // default
        QJsonValue({
            {"name","default"},
            {"text_color","#fff"},
            {"background_color","#FFCDD2"}
        }),


       // sport
        QJsonValue({

            {"name","sport"},
            {"text_color","#fff"},
            {"background_color","#4CAF50"}
        }),

        // dance
         QJsonValue({

             {"name","dance"},
             {"text_color","#fff"},
             {"background_color","#4E342E"}
         }),


        // event
         QJsonValue({

             {"name","dance"},
             {"text_color","#fff"},
             {"background_color","#FFEB3B"}
         }),

        // birthday
        QJsonValue({

            {"name","birthday"},
            {"text_color","#fff"},
            {"background_color","#607D8B"}
        }),

        // daily
        QJsonValue({

            {"name","daily"},
            {"text_color","#fff"},
            {"background_color","#03A9F4"}
        }),


        // high
        QJsonValue({

            {"name","high"},
            {"text_color","#fff"},
            {"background_color","#E91E63"}
        }),

        // low
        QJsonValue({

            {"name","low"},
            {"text_color","#fff"},
            {"background_color","#009688"}
        })
    };

    QJsonDocument saveTypesColorMap(typesColorMap);
    typesFile.write(saveTypesColorMap.toJson());
    return true;
}

bool Reset::resetTasks()
{
    QFile tasksFile("tasks.json");

    if(!tasksFile.open(QIODevice::WriteOnly)){
        // TODO handle openning error
        return false;
    }

    auto firstRunTask=new Task;

    firstRunTask->setName("Prise en main");

    firstRunTask->setStartDate(QDate().currentDate());
    firstRunTask->setEndDate(QDate().currentDate());

    firstRunTask->setStartTime(QTime().currentTime());
    firstRunTask->setEndTime(QTime().currentTime().addSecs(300));

    firstRunTask->setComment("Feel free to use this amazing software");

    QJsonArray defaultTask
    {
        QJsonValue({
                       {"task_name",firstRunTask->name()},
                       {"start_date", firstRunTask->startDate().toString("dd.MM.yyyy")},
                       {"end_date", firstRunTask->endDate().toString("dd.MM.yyyy")},

                       {"start_time", firstRunTask->startTime().toString()},
                       {"end_time", firstRunTask->endTime().toString()},

                       {"type", "low"},
                       {"comment", firstRunTask->comment()}
                   })
    };
    tasksFile.write(QJsonDocument(defaultTask).toJson());
    return true;
}
