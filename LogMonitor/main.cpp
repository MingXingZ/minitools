#include <QApplication>
#include <QFile>
#include <QIODevice>
#include <QTime>
#include "qdebug.h"

QString getDuration(QTime startTime, QTime endTime);
void storeTimeInfo(QString timeInfo);
void monitorBootupLog();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    monitorBootupLog();
    return a.exec();
}


void monitorBootupLog()
{
    QFile file("/home/mingxing/bootup.log");


    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"open log file failed.";
    }else{
        qDebug()<<"open log file succeeded.";
    }

    //move to the end of the file
    quint64 startingPos;
    startingPos = file.size();
    file.seek(startingPos);


    QTime startTime = QTime::currentTime();
    qDebug()<<"start monitoring the target app("<<startTime.toString()<<").."<<endl;
    while(true)
    {
        QByteArray lineRead = file.readAll();
        if(lineRead.contains("netx_version"))
        {
            QTime endTime = QTime::currentTime();
            qDebug()<<"the monitored app is now up and running("<<endTime.toString()<<").."<<endl;
            qDebug()<<"duration:"<<getDuration(startTime, endTime)<<endl;

            //store bootup time info
            QString timeInfo = "start time "+startTime.toString()+
                    "\nend time   "+endTime.toString()+
                    "\nduration   "+getDuration(startTime, endTime)+"\n\n";
            storeTimeInfo(timeInfo);
            //reboot the app
		//system("reboot");
        }

        //keep the reading buffer size reasonable
        quint64 currentSize = file.size();
        if(currentSize - startingPos > 1024 * 64)
        {
            //move to the next reading position
            startingPos = currentSize;
            file.seek(startingPos);
        }

    }
}

QString getDuration(QTime startTime, QTime endTime)
{
    int hourMargin = endTime.hour() - startTime.hour();
    int minuteMargin = endTime.minute() - startTime.minute();
    int secondMargin = endTime.second() - startTime.second();

    if(hourMargin < 0)
    {
        return "different days, checkout the start time and end time";
    }

    if(minuteMargin < 0)
    {
        minuteMargin = 60 - startTime.minute() + endTime.minute();
        hourMargin -= 1;
    }

    if(secondMargin < 0)
    {
        secondMargin = 60 - startTime.second() + endTime.second();
        minuteMargin -= 1;
    }

    QString duration;
    duration.sprintf("%02d:%02d:%02d", hourMargin, minuteMargin, secondMargin);
    return duration;

}

void storeTimeInfo(QString timeInfo)
{
    QFile file("/home/mingxing/timespent_tobootup.log");

    //open file
    if(!file.open(QIODevice::Append)){
        qDebug()<<"open file failed.";
    }else{
        //qDebug()<<"open file succeeded.";
    }
    int writtenLength = file.write(timeInfo.toLatin1(),timeInfo.length());
    if(writtenLength == -1)
    {
        qDebug()<<"written time info failed"<<endl;
    }
    file.close();
}
