#include "processmodifyxml.h"
#include <QStringList>
#include <iostream>
#include "pugixml/pugixml.hpp"
#include "qdebug.h"
#include <unistd.h>

using namespace pugi;

ProcessModifyXml::ProcessModifyXml()
{
    outputXml = "../execution/xmls/testoutput.xml";
    inputXml = "../execution/xmls/test.xml";
}



void ProcessModifyXml::processFile(QString& fileTextContent)
{
    QStringList signalInfo = fileTextContent.split(',');
    if(signalInfo.size() != 2)
    {
        return;
    }

    std::string oldName = signalInfo.first().trimmed().toStdString();
    std::string newName = signalInfo.last().trimmed().toStdString();
    modifyXml(oldName, newName);


}


void ProcessModifyXml::modifyXml(std::string oldName, std::string newName)
{
//    walker.setSigInfo(oldName, newName);
//    //pugixml 初体验
//    xml_document doc;
//    xml_parse_result res = doc.load_file(inputXml.c_str());
//    if (res)
//    {
//        //std::cout << "load result:" << res.description() << std::endl;
//    }else{
//        qDebug() << "xml parsed failed.";
//        return;
//    }


//    //-----------------------------access document data-------------------------------
//    //traversal taste
////    xml_node rootNode = doc.first_child();
////    std::cout << "node name:" << rootNode.name() << std::endl;

//    //walk through the tree recursively
//    //xml_tree_walker* walker =  new signal_walker();   //inheritance in cpp in private by default
//    doc.traverse(walker);
//    bool isSuccessful = doc.save_file(outputXml.c_str());
//    if(!isSuccessful)
//    {
//        qDebug() << "save xml file failed.";
//    }
//    sleep(1);
//    //qDebug() << "Is saving file successful: " << isSuccessful;
}


