#include "processnewsignal.h"
#include "qdebug.h"
#include <QFile>




//xml related


































void storeResult(QString content);
QString addUnderLine(QString& originalLine);

ProcessNewSignal::ProcessNewSignal()
{

}



void ProcessNewSignal::processFile(QString& fileTextContent)
{
    //qDebug()<< fileTextContent << endl;
    QStringList lineComponents = fileTextContent.split(',');
    QString oldName = lineComponents.first().trimmed();
    QString newName = lineComponents.last().trimmed();
    //qDebug()<< oldName << " : "<< newName <<endl;
    QString strWithUnderscore = addUnderLine(newName);

    QString targetString = oldName + ",             " + strWithUnderscore + "\n";

    //save the result to a file   (a file library should be created in your repositroy
    storeResult(targetString);
    //qDebug()<<
}

//just a quick writing, will move to a utility place
QString space2underscore(QString& stringWithSpaces)
{
    std::string text = stringWithSpaces.toStdString();
    for(std::string::iterator it = text.begin(); it != text.end(); ++it) {
            if(*it == ' ') { //the logic here need to improve, more than one spaces? spaces like /t?
                *it = '_';
            }
        }
    QString resultStr = QString::fromStdString(text);
    return resultStr;
}


QString addUnderLine(QString& originalLine)
{
    //qDebug() << space2underscore(originalLine) <<endl;
    return space2underscore(originalLine);

}

void storeResult(QString content)
{
    QFile file("//home/mingxing/development/tools/signal_change_result.txt");

    //open file
    if(!file.open(QIODevice::Append)){
        qDebug()<<"open file failed.";
    }else{
        //qDebug()<<"open file succeeded.";
    }
    int writtenLength = file.write(content.toLatin1(),content.length());
    if(writtenLength == -1)
    {
        qDebug()<<"written content failed"<<endl;
    }
    file.close();
}



