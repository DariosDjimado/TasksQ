#include "commands.h"

AddTaskCommand::AddTaskCommand(QTableWidget *table,QHash<int, Task *> * taskMap, TaskListController *taskListController, QUndoCommand *parent)
: QUndoCommand (parent),
  m_taskListController(taskListController),
  m_table(table),
  m_taskMap(taskMap)
{

}

AddTaskCommand::~AddTaskCommand()
{
    delete m_table;
    delete m_taskListController;
    delete m_task;
}

void AddTaskCommand::undo()
{
    if(m_taskListController->deleteTask(m_task)){
        m_taskMap->remove(m_localTaskMap.value(m_task));
        m_table->removeRow(m_localTaskMap.value(m_task));
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
        displayTask(true,row,task);
        m_localTaskMap.insert(task,row);
    }
}

void AddTaskCommand::displayTask(bool isNew, int row, Task *task)
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

    if(isNew){
        m_taskMap->insert(row,task);
    }
}
