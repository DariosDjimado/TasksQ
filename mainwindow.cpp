#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QPropertyAnimation>

#include <iostream>
using namespace std;

#include <QFile>
#include <QTextStream>


MainWindow::MainWindow(TaskListController * controller,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_controller(controller)
{
    Q_ASSERT(controller!=nullptr);
    ui->setupUi(this);

    init();
    setupConfig();
    setupConnections();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createTask()
{
    auto task=m_controller->createTask();
    if(task){

        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        auto rowCount=ui->tableWidget->rowCount()-1;

        displayTask(rowCount,task);
    }
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
                m_controller->saveData();
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

            ui->editPageNameInput->setText(task->name());

            ui->editPageStartDateInput->setDate(task->startDate());
            ui->editPageEndDateInput->setDate(task->endDate());

            ui->editPageStartTimeInput->setTime(task->startTime());
            ui->editPageEndTimeInput->setTime(task->endTime());
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

                task->setSaved(true);

                ui->tableWidget->setItem(row,NAME,new QTableWidgetItem(task->name()));
                ui->tableWidget->setItem(row,START_DATE, new QTableWidgetItem(task->startDate().toString("dd.MM.yyyy")));
                ui->tableWidget->setItem(row,START_TIME, new QTableWidgetItem(task->startTime().toString("hh.mm.ss")));
                ui->tableWidget->setItem(row,END_DATE, new QTableWidgetItem(task->endDate().toString("dd.MM.yyyy")));
                ui->tableWidget->setItem(row,END_TIME, new QTableWidgetItem(task->endTime().toString("hh.mm.ss")));
                ui->tableWidget->setItem(row,TYPE,new QTableWidgetItem(QString::number(task->type())));
                ui->tableWidget->setItem(row,COMMENT,new QTableWidgetItem(task->comment()));


                //********
                 m_controller->saveData();


                discardTask();
            }
        }
}

void MainWindow::discardTask()
{
    ui->stackedWidget->setCurrentWidget(ui->listPage);
    ui->menuTasks->setEnabled(true);
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
    m_controller->loadData();
    for(int i=0;i<m_controller->getSize();i++){

        auto task=m_controller->getTask(i);
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        auto rowCount=ui->tableWidget->rowCount()-1;

        displayTask(rowCount,task);
    }

}

void MainWindow::displayTask(int row, Task *task)
{
    ui->tableWidget->setItem(row,NAME,new QTableWidgetItem(task->name()));
    ui->tableWidget->setItem(row,START_DATE, new QTableWidgetItem(task->startDate().toString("dd.MM.yyyy")));
    ui->tableWidget->setItem(row,START_TIME, new QTableWidgetItem(task->startTime().toString("hh.mm.ss")));
    ui->tableWidget->setItem(row,END_DATE, new QTableWidgetItem(task->endDate().toString("dd.MM.yyyy")));
    ui->tableWidget->setItem(row,END_TIME, new QTableWidgetItem(task->endTime().toString("hh.mm.ss")));
    ui->tableWidget->setItem(row,TYPE,new QTableWidgetItem(QString::number(task->type())));
    ui->tableWidget->setItem(row,COMMENT,new QTableWidgetItem(task->comment()));

    m_taskMap.insert(row,task);
}
