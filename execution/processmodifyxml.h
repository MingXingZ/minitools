#ifndef PROCESSMODIFYXML_H
#define PROCESSMODIFYXML_H
#include "iprocesslogic.h"
#include "pugixml/signal_walker.h"


class ProcessModifyXml : public IProcessLogic
{
public:
    ProcessModifyXml();
    virtual void processFile(QString& fileTextContent) override;
    void modifyXml(std::string oldName, std::string newName);
    virtual ~ProcessModifyXml(){}
    //void setDoc(pugi::xml_document& doc){m_doc = doc;}
private:
    signal_walker walker;
    std::string outputXml;
    std::string inputXml;
    pugi::xml_document m_doc;
};

#endif // PROCESSMODIFYXML_H
