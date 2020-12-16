#include <QApplication>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include "qdebug.h"
#include <QThread>


quint64 getMicroseconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    quint64 microSeconds = tv.tv_sec * 1000000 + tv.tv_usec;
    return microSeconds;
}


quint64 getMicroSecsElapsed(quint64 startMicroSecs)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    quint64 currentMicroSecs = tv.tv_sec * 1000000 + tv.tv_usec;
    return currentMicroSecs - startMicroSecs;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    struct timeval tv;
//    gettimeofday(&tv, NULL);

//    quint64 microSeconds = tv.tv_sec * 1000000 + tv.tv_usec;
//    qDebug()<<tv.tv_sec<<endl; // 秒
//    qDebug()<<tv.tv_sec * 1000 + tv.tv_usec / 1000<<endl; // 毫秒
//    qDebug()<<microSeconds; // 徽秒

//    qDebug()<<"------------------sleep three seconds----------------"<<endl;
//    sleep(3);

//    gettimeofday(&tv, NULL);
//    qDebug()<<tv.tv_sec<<endl; // 秒
//    qDebug()<<tv.tv_sec * 1000 + tv.tv_usec / 1000<<endl; // 毫秒
//    qDebug()<<tv.tv_sec * 1000000 + tv.tv_usec; // 徽秒


    quint64 startMicro = getMicroseconds();
    QThread::msleep(10);
    quint64 timeElapsed = getMicroSecsElapsed(startMicro);
    qDebug()<<"time elapsed: "<<QString::number(timeElapsed)<<endl;


    //    qDebug()<<"------------------sleep three seconds----------------"<<endl;
    //    sleep(3);

    return a.exec();
}


