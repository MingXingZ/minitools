#include <QApplication>
#include <QTime>
#include <QFile>
#include <QIODevice>
#include <QtGlobal>
#include <QThread>
#include "qdebug.h"

quint64 getRandomNumber(quint64 max);
QString getRandomString();
QString getDuration(QTime startTime, QTime endTime);
void writeLog();


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //simulate writing log
    writeLog();
    return a.exec();
}

void writeLog()
{
   QFile file("/home/mingxing/bootup.log");

   //open file
   if(!file.open(QIODevice::Append)){
       qDebug()<<"open file failed.";
   }else{
       //qDebug()<<"open file succeeded.";
   }

   //simulate boot up the app
    quint64 writtingCount = 1000 + getRandomNumber(1000);
    QTime startTime = QTime::currentTime();
    qDebug()<<"start the simulated app("<<startTime.toString()<<")"<<endl;
    while(writtingCount > 0)
    {
        //move to the end of the file
        quint64 pos;
        pos = file.size();
        file.seek(pos);
        //write a random string
        QString content = getRandomString()+"\n";
        file.write(content.toLatin1(),content.length());
        QThread::msleep(10);
        writtingCount--;
        if(writtingCount == 0)
        {
            //time to write the target string(means system is up and running)
            QString targetString = "\nxxxxxxx  netx_version xxxxxx\n\n";
            pos = file.size();
            file.seek(pos);
            file.write(targetString.toLatin1(),targetString.length());
            QTime endTime = QTime::currentTime();
            qDebug()<<"the simulated app is up and running("<<endTime.toString()<<")"<<endl;
            qDebug()<<"duration:"<<getDuration(startTime, endTime)<<endl;

        }
    }


    //continue to write some log after booting up
    for(int i=0; i<100; ++i)
    {
        quint64 pos = file.size();
        file.seek(pos);
        QThread::msleep(100);
        QString randomString = getRandomString()+"\n";
        file.write(randomString.toLatin1(),randomString.length());
    }
    //close file
    file.close();
}


quint64 getRandomNumber(quint64 max)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int randomNum = qrand()%max;
    return randomNum;
}

QString getRandomString()
{
   QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 /\\-';:*$#@!^");
   int randomStringLength = 60; // assuming we want a string of 60 characters

   QString randomString;
   for(int i=0; i<randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
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



