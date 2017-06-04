#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reset.h"
#include "commands.h"

#include <QPushButton>
#include <QPropertyAnimation>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>


#include <iostream>
using namespace std;



MainWindow::MainWindow(TaskListController * controller, TaskTypeListController *typeController, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_controller(controller),
    m_typeController(typeController)
{
    Q_ASSERT(controller!=nullptr);
    Q_ASSERT(typeController!=nullptr);
    m_undoStack=new QUndoStack(this);
    ui->setupUi(this);

    if(config()){
        qWarning("okok");
    }
        ;

    // initialize the session
    init();

    //
    setupConfig();

    // make connections
    setupConnections();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createTask()
{
    QUndoCommand *ta=new AddTaskCommand(ui->tableWidget,&m_taskMap, m_controller);
     m_undoStack->push(ta);
    ui->actionUndo->setEnabled(m_undoStack->canUndo());
}

void MainWindow::deleteTask()
{
    auto row=ui->tableWidget->currentRow();
    if(row>=0){
        auto task=m_taskMap.value(row);

        if(task){
            if(m_controller->deleteTask(task)){
                m_taskMap.remove(row);
                ui->tableWidget->removeRow(row);


                //*******
                m_controller->saveTasks();
            }
        }
    }
}

void MainWindow::editTask()
{
    auto item=ui->tableWidget->currentRow();
    if(item>=0){
        auto task=m_taskMap.value(item);

        if(task){
            ui->stackedWidget->setCurrentWidget(ui->editPage);

            ui->menuTasks->setEnabled(false);
            ui->actionAdd->setEnabled(false);
            ui->actionRemove->setEnabled(false);

            // name
            ui->editPageNameInput->setText(task->name());
            // dates
            ui->editPageStartDateInput->setDate(task->startDate());
            ui->editPageEndDateInput->setDate(task->endDate());
            // times
            ui->editPageStartTimeInput->setTime(task->startTime());
            ui->editPageEndTimeInput->setTime(task->endTime());
            // type
            ui->editPageTypeInput->setCurrentIndex(m_typeMap.value(task->type()));
        }
    }
}

void MainWindow::saveTask()
{
    auto row=ui->tableWidget->currentRow();
        if(row>=0){
            auto task=m_taskMap.value(row);

            if(task){
                task->setName(ui->editPageNameInput->text());

                task->setStartDate(ui->editPageStartDateInput->date());
                task->setEndDate(ui->editPageEndDateInput->date());

                task->setStartTime(ui->editPageStartTimeInput->time());
                task->setEndTime(ui->editPageEndTimeInput->time());

                task->setType(m_typeController->getTaskTypeByName(ui->editPageTypeInput->currentText()));


                task->setSaved(true);

                displayTask(false,row,task);

                //********
                 m_controller->saveTasks();


                discardTask();
            }
        }
}

void MainWindow::discardTask()
{
    ui->stackedWidget->setCurrentWidget(ui->listPage);
    ui->menuTasks->setEnabled(true);
    ui->actionAdd->setEnabled(true);
    ui->actionRemove->setEnabled(true);
}

void MainWindow::undo()
{
    m_undoStack->undo();
    ui->actionUndo->setEnabled(m_undoStack->canUndo());
    ui->actionRedo->setEnabled(m_undoStack->canRedo());
}

void MainWindow::redo()
{
    m_undoStack->redo();
    ui->actionUndo->setEnabled(m_undoStack->canUndo());
    ui->actionRedo->setEnabled(m_undoStack->canRedo());
}

void MainWindow::setupConnections()
{
    connect(ui->actionAdd, SIGNAL(triggered(bool)),
            this,SLOT(createTask()));

    connect(ui->actionRemove, &QAction::triggered,
            this, &MainWindow::deleteTask);

    connect(ui->actionEdit, &QAction::triggered,
            this, &MainWindow::editTask);

    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::clicked,
            this, &MainWindow::saveTask);

    connect(ui->buttonBox->button(QDialogButtonBox::Discard), &QPushButton::clicked,
                    this, &MainWindow::discardTask);


    connect(ui->actionUndo, &QAction::triggered,
            this, &MainWindow::undo);

    connect(ui->actionRedo, &QAction::triggered,
            this, &MainWindow::redo);

    connect(ui->actionExit, &QAction::triggered,
            this, &MainWindow::close);

}

void MainWindow::setupConfig()
{

    QStringList titles;
    titles<<"Task name"<<"Start Date"<<"Start Time"<<"End Date"<<"End Time"<<"Type"<<"Comment";
    ui->tableWidget->setHorizontalHeaderLabels(titles);



    QGraphicsScene *scene=new QGraphicsScene(0,0,300,300, ui->graphicsView);
    scene->setBackgroundBrush(Qt::yellow);

    QPen linePen(Qt::blue);
    linePen.setWidth(5);

    scene->addLine(-50,-50,100,-50,linePen);

    ui->graphicsView->setScene(scene);
}

void MainWindow::init()
{
    // Load the Types
    m_typeController->loadTaskTypes();

    // Load the Tasks
    m_controller->loadTasks();

    // display the Tasks;
    for(int i=0;i<m_controller->getSize();i++){

        auto task=m_controller->getTask(i);
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        auto rowCount=ui->tableWidget->rowCount()-1;

        displayTask(true,rowCount,task);
    }

    // Types combo box
    for(int i=0;i<m_typeController->getSize();i++){
        auto type=m_typeController->getTaskTypeByPosition(i);
        ui->editPageTypeInput->addItem(type->name());
        m_typeMap.insert(type,i);
    }
}

void MainWindow::displayTask(bool isNew, int row, Task *task)
{

    ui->tableWidget->setItem(row,Task::NAME,new QTableWidgetItem(task->name()));
    ui->tableWidget->setItem(row,Task::START_DATE, new QTableWidgetItem(task->startDate().toString("dd.MM.yyyy")));
    ui->tableWidget->setItem(row,Task::START_TIME, new QTableWidgetItem(task->startTime().toString()));
    ui->tableWidget->setItem(row,Task::END_DATE, new QTableWidgetItem(task->endDate().toString("dd.MM.yyyy")));
    ui->tableWidget->setItem(row,Task::END_TIME, new QTableWidgetItem(task->endTime().toString()));
    ui->tableWidget->setItem(row,Task::TYPE,new QTableWidgetItem(task->type()->name()));
    ui->tableWidget->setItem(row,Task::COMMENT,new QTableWidgetItem(task->comment()));

    for(int i=0; i<ui->tableWidget->columnCount();i++){
        ui->tableWidget->item(row,i)->setBackgroundColor(QColor(task->type()->backgroundColor()));
        ui->tableWidget->item(row,i)->setTextColor(QColor(task->type()->textColor()));

    }

    if(isNew){
        m_taskMap.insert(row,task);
    }
}

bool MainWindow::config()
{
    QFile configFile("config.json");

    if(!configFile.exists()){ // if the file doesn't exist, it means fresh install
        if(!configFile.open(QIODevice::WriteOnly)){
            // TODO handle openning error
            return false;
        }
        QJsonObject configObject
        {
            {"app_name", "tasksQ"},
            {"app_version","alpha"},
            {"reset_on_start","false"}
        };
        configFile.write(QJsonDocument(configObject).toJson());
        return Reset::doReset();

    }


    if(!configFile.open(QIODevice::ReadOnly)){
        // TODO handle openning error
        return false;
    }

    QByteArray config=configFile.readAll();
    QJsonDocument configDoc(QJsonDocument::fromJson(config));
    QJsonObject configObject(configDoc.object());

    if(configObject.take("reset_on_start").toString()=="true"){
        return Reset::doReset();
    }

    return true;
}
