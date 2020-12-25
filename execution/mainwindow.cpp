#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include "qdebug.h"
#include "processchangexml.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QFile file("/home/mingxing/development/tools/signal_change.txt");
    QFile file("/home/mingxing/development/tools/signal_change_result.txt");
    if(file.exists())
    {
        qDebug()<<"exist"<<endl;
    }

    bool res = file.open(QIODevice::ReadOnly | QIODevice::Text);

    if (res)
    {

        QString line;

        QTextStream in(&file);  //用文件构造流

        line = in.readLine();//读取一行放到字符串里

        int lineNumber = 0;
        if(!line.isNull())
        {
            //add process logic for each line
            //processLogics.append(new ProcessNewSignal());
            processLogics.append(new ProcessChangeXml());


            //apply process logic for each line
            do
            {

                foreach (IProcessLogic* processLogic, processLogics)
                {
                    processLogic->processFile(line);
                }
                lineNumber++;
                line = in.readLine();

            }while(!line.isNull());
        }
        qDebug()<< "total:" << lineNumber << endl;
        file.close();
    }else{
        qDebug() << file.error() << endl;
        qDebug() << file.errorString();
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}
