#ifndef PROCESSNEWSIGNAL_H
#define PROCESSNEWSIGNAL_H
#include "iprocesslogic.h"
#include <QDomDocument>
class ProcessNewSignal : public IProcessLogic
{
public:
    ProcessNewSignal();
    virtual void processFile(QString& fileTextContent);
    bool openXmlFile(QString FilePath);
    bool changeSave();
    QDomDocument m_doc;

};

#endif // PROCESSNEWSIGNAL_H
