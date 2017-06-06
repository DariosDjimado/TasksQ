#include "commands.h"

BaseCommand::BaseCommand(QTableWidget *table, QHash<QTableWidgetItem *, Task *> *taskMap, TaskListController *taskListController, QUndoCommand *parent)
    :QUndoCommand(parent),
      m_table(table),
      m_taskMap(taskMap),
      m_taskListController(taskListController)

{
    Q_ASSERT(table!=nullptr);
    Q_ASSERT(taskMap!=nullptr);
    Q_ASSERT(m_taskListController!=nullptr);
}

void BaseCommand::displayTask(int row, Task *task)
{
    m_table->setItem(row,Task::NAME,new QTableWidgetItem(task->name()));
    m_table->setItem(row,Task::START_DATE, new QTableWidgetItem(task->startDate().toString("dd.MM.yyyy")));
    m_table->setItem(row,Task::START_TIME, new QTableWidgetItem(task->startTime().toString()));
    m_table->setItem(row,Task::END_DATE, new QTableWidgetItem(task->endDate().toString("dd.MM.yyyy")));
    m_table->setItem(row,Task::END_TIME, new QTableWidgetItem(task->endTime().toString()));
    m_table->setItem(row,Task::TYPE,new QTableWidgetItem(task->type()->name()));
    m_table->setItem(row,Task::COMMENT,new QTableWidgetItem(task->comment()));

    for(int i=0; i<m_table->columnCount();i++){
        m_table->item(row,i)->setBackgroundColor(QColor(task->type()->backgroundColor()));
        m_table->item(row,i)->setTextColor(QColor(task->type()->textColor()));
    }

    m_taskMap->insert(m_table->item(row,Task::NAME),task);
}

AddTaskCommand::AddTaskCommand(QTableWidget *table,QHash<QTableWidgetItem *, Task *> *taskMap, TaskListController *taskListController, QUndoCommand *parent)
    :BaseCommand (table,taskMap, taskListController,parent)
{

}

AddTaskCommand::~AddTaskCommand()
{

}

void AddTaskCommand::undo()
{
    if(m_taskListController->deleteTask(m_task)){
        m_taskMap->remove(m_localTaskMap.value(m_task));
        m_table->removeRow(m_localTaskMap.value(m_task)->row());
        //*******
        m_taskListController->saveTasks();
    }
}

void AddTaskCommand::redo()
{
    Task * task=m_taskListController->createTask();
    if(task){
        m_task=task;
        m_table->insertRow(m_table->rowCount());
        auto row=m_table->rowCount()-1;
        displayTask(row,task);
        m_localTaskMap.insert(task,m_table->item(row,Task::NAME));
    }
}


DeleteCommand::DeleteCommand(QTableWidget *table, QHash<QTableWidgetItem *, Task *> *taskMap, TaskListController *taskListController, QUndoCommand *parent)
    :BaseCommand (table,taskMap,taskListController,parent)
{

}

DeleteCommand::~DeleteCommand()
{

}

void DeleteCommand::undo()
{
    if(m_task!=nullptr){
        m_task->setSaved(true);
        m_table->insertRow(m_row);
        displayTask(m_row,m_task);

        m_taskListController->saveTasks();
    }
}

void DeleteCommand::redo()
{
    auto row=m_table->currentRow();
    if(row>=0){
        // we have to keep the row for futur reinserting element
        m_row=row;
        auto task=m_taskMap->value(m_table->item(row,Task::NAME));
        if(task){
            // stock the reference for undo purpose
            m_task=task;

            // set saved at false
            m_task->setSaved(false);
            m_taskMap->remove(m_table->item(row,Task::NAME));
            m_table->removeRow(row);

            // since we are setting saved at false this task will not save
            m_taskListController->saveTasks();
        }
    }
}
