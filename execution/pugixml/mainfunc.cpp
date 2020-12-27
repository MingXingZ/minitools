// UpdateSignal.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "pugixml.hpp"
#include "signal_walker.h"

using namespace pugi;
int mainfunc()
{
    //SW85-694_C1_origin.xml
    //test.xml
    std::string xmlSourceFile = "../xmls/redbox/test.xml";
    std::string xmlOutputFile = "../xmls/redbox/testUpdated.xml";


    //pugixml 初体验
    xml_document doc;
    xml_parse_result res = doc.load_file(xmlSourceFile.c_str());
    std::cout << "load result:" << res.description() << std::endl;
    if (res)
    {
        std::cout << "xml [" << xmlSourceFile << "] parsed without errors. " 
                  << "attribute value->[configuration:" << doc.child("configuration").attribute("id").value()
                  << "]" << std::endl;
    }


    //-----------------------------access document data-------------------------------
    //traversal taste
    xml_node rootNode = doc.first_child();
    std::cout << "node name:" << rootNode.name() << std::endl;

    //walk through the tree recursively
    //xml_tree_walker* walker =  new signal_walker();   //inheritance in cpp in private by default
    signal_walker walker;
    doc.traverse(walker);
    bool isSuccessful = doc.save_file(xmlOutputFile.c_str());
    std::cout << "Is saving file successful: " << isSuccessful << std::endl;
    std::cout << "number of signals: " << walker.sig_num << std::endl;


    //--------------------------------modify document data-----------------------------------

    //try to change a specific attribute of a node
    /*xml_attribute id = rootNode.attribute("id");
    std::cout << id.set_name("idd") << "," << id.set_value("newvalue") << std::endl;
    std::cout << "new attribute: " << id.name() << ", " << id.value() << std::endl;*/






    //--------------------------------save document data-------------------------------------























    //std::cin.get();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
