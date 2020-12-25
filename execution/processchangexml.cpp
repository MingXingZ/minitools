#include "processchangexml.h"
#include "qdebug.h"
#include <QFile>
#include <QDomNode>
#include "nodeiterator.h"

ProcessChangeXml::ProcessChangeXml()
{
    //m_fileName = "/home/mingxing/development/tools/SW85-694_C1_origin.xml";
    m_fileName = "/home/mingxing/development/tools/test.xml";
}

bool ProcessChangeXml::openXmlFile(QString FilePath)
{
    QFile file( FilePath );
    if( !file.open( QFile::ReadOnly | QFile::Text  ) )
    {
        qDebug() << QObject::tr("error::ParserXML->OpenXmlFile->file.open->%s\n") << FilePath;
        return false;
    }
    if( !m_doc.setContent( &file ) )
    {
        qDebug() << QObject::tr("error::ParserXML->OpenXmlFile->doc.setContent\n") << FilePath;
        file.close();
        return false;
    }
    file.close();
    return true;

}

//void recursiveChange(QDomNode firstNode, QString oldName, QString newName)
//{
//    QDomElement firstELement = firstNode.toElement();
//    if(firstELement.tagName() == "signal" || firstELement.tagName() == "insignal" || firstELement.tagName() == "outsignal" ||)
//    {
//        if(firstELement.hasAttribute("name") && firstELement.attribute("name") == oldName)
//        {
//            firstELement.setAttribute("name", newName);
//        }
//    }
//}

bool ProcessChangeXml::changeSave(QString oldName, QString newName)
{

    QFile file(m_fileName);
    if( !file.open( QFile::ReadWrite | QFile::Text  ) )
    {
        qDebug() << QObject::tr("error::ParserXML->OpenXmlFile->file.open->%s\n") << m_fileName;
        return false;
    }
    if( !m_doc.setContent( &file ) )
    {
        qDebug() << QObject::tr("error::ParserXML->OpenXmlFile->doc.setContent\n") << m_fileName;
        file.close();
        return false;
    }

    //修改保存xml

    QDomElement root = m_doc.documentElement();
    QString rootName = root.tagName();
    if(rootName != "configuration")
           return false;


    QDomNode current;

    QString name;
    int i = 0;

    for (NodeIterator *it = new NodeIterator((QDomNode)root); it->hasNext();)
    {

        current = it->next();


        if (!current.isNull() && current.isElement())
        {

           if( current.nodeName() == "object" )
           {

           }
        }
    }
    qDebug()<<"i:"<<i<<endl;
    QTextStream textStream(&file);

    m_doc.save(textStream, 4);
    file.close();

    return true;

























//     QFile filexml("/home/qust/qt/XML/2.xml");

//     if( !filexml.open( QFile::WriteOnly | QFile::Truncate) ){

//         qWarning("error::ParserXML->writeOperateXml->file.open\n");

//         return false;

//     }

//     QTextStream ts(&filexml);

//     ts.reset();

//     ts.setCodec("utf-8");

//     m_doc.save(ts, 4, QDomNode::EncodingFromTextStream);

//     filexml.close();

    return true;
}


void ProcessChangeXml::processFile(QString& fileTextContent)
{
    QStringList lineComponents = fileTextContent.split(',');
    QString oldName = lineComponents.first().trimmed();
    QString newName = lineComponents.last().trimmed();
    changeSave(oldName, newName);


}
