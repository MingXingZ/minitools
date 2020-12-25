#ifndef PROCESSCHANGEXML_H
#define PROCESSCHANGEXML_H
#include "iprocesslogic.h"
#include <QDomDocument>

class ProcessChangeXml : public IProcessLogic
{
public:
    ProcessChangeXml();
    virtual void processFile(QString& fileTextContent);
    bool openXmlFile(QString FilePath);
    bool changeSave(QString oldName, QString newName);

    QDomDocument m_doc;
    QString m_fileName;
};

#endif // PROCESSCHANGEXML_H
