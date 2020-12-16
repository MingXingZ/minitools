#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile file("/home/mingxing/MFT/log/114/executionTime.log");
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

            qDebug() << line;
            int i = 1;
            int targetNumber = 0;
            while(!line.isNull())//字符串有内容

            {
                ++i;
                line=in.readLine();//循环读取下行

                QString number = line.split('$').last();
                QString former = line.split('$').first();
                int time = number.toInt();
                if(time > 200 )//&& former.contains("total"))
                {
                    qDebug()<<i<<":"<<time;
                        targetNumber++;
                }


//                QString total = line.split(':').last();
//                if(total.toInt() > 100)
//                {
//                    qDebug()<<i<<":"<<total;
//                    targetNumber++;
//                }



            }
            qDebug()<<"total:"<<targetNumber<<endl;
            file.close();
        }else{
            qDebug()<<file.error()<<endl;
            qDebug()<<file.errorString();
        }


}

MainWindow::~MainWindow()
{
    delete ui;
}
