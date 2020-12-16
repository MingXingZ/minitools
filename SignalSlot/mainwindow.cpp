#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainTaskTimer = new QTimer();
    subTask1Timer = new QTimer();
    subTask2Timer = new QTimer();
    subTask3Timer = new QTimer();

    mainTaskTimer->setInterval(1000);
    subTask1Timer->setInterval(1000);
    subTask2Timer->setInterval(1000);
    subTask3Timer->setInterval(1000);

    objectiveTaskTimer = new QTimer();
    objectiveTaskTimer->setInterval(100);

    connect(mainTaskTimer, SIGNAL(timeout()), this, SLOT(mainTask()), Qt::DirectConnection);
    connect(subTask1Timer, SIGNAL(timeout()), this, SLOT(subTask1()), Qt::DirectConnection);
    connect(subTask2Timer, SIGNAL(timeout()), this, SLOT(subTask2()), Qt::DirectConnection);
    connect(subTask3Timer, SIGNAL(timeout()), this, SLOT(subTask3()), Qt::DirectConnection);
    connect(objectiveTaskTimer, SIGNAL(timeout()), this, SLOT(objectiveTask()), Qt::DirectConnection);

    //test case 1: perform the task within the mainTask slot(sleep 3 seconds to mimic the actual scenario)
//    mainTaskTimer->start();
//    objectiveTaskTimer->start();

//    test result:
//    current time: QTime("23:08:25.452")

//    current time: QTime("23:08:28.453")

//    current time: QTime("23:08:31.455")

//    current time: QTime("23:08:34.456")

//    current time: QTime("23:08:37.456")

    //test case 2: separate the task into three subtask slots(each subtask sleep 1 seconds to mimic the actual scenario)
    subTask1Timer->start();
    subTask2Timer->start();
    subTask3Timer->start();
    objectiveTaskTimer->setSingleShot(true);
    objectiveTaskTimer->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mainTask()
{
    QThread::sleep(3);
}

void MainWindow::subTask1()
{
    QThread::sleep(1);
}

void MainWindow::subTask2()
{
    QThread::sleep(1);
}

void MainWindow::subTask3()
{
    QThread::sleep(1);
}


void MainWindow::objectiveTask()
{
    qDebug()<<"current time:"<<QTime::currentTime()<<endl;
    QTimer::singleShot(500, this, &MainWindow::objectiveTask);
}
