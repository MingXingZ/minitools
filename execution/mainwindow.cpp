#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include "qdebug.h"
#include "processmodifyxml.h"
#include <iostream>
using namespace pugi;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QFile file("/home/mingxing/development/tools/signal_change.txt");
    //QFile file("/home/mingxing/development/tools/signal_change_result.txt");
    std::string outputXml = "../execution/xmls/SW85-694_C1_updated.xml";
    std::string inputXml = "../execution/xmls/SW85-694_C1_origin.xml";
    QFile file("../execution/xmls/SW85-694_C1_origin.xml");
    if(file.exists())
    {
        qDebug()<<"exist"<<endl;
    }

    //pugixml 初体验
    xml_document doc;
    xml_parse_result resd = doc.load_file(inputXml.c_str());
    if (resd)
    {
        //std::cout << "load result:" << res.description() << std::endl;
    }else{
        qDebug() << "xml parsed failed.";
        return;
    }
    bool res = file.open(QIODevice::ReadOnly | QIODevice::Text);

    if (res)
    {

        QString line;

        QTextStream in(&file);  // construct text stream using the file

        line = in.readLine();//read one line

        int lineNumber = 0;
        if(!line.isNull())
        {
            //add process logic for each line
            //processLogics.append(new ProcessNewSignal());
            //processLogics.append(new ProcessChangeXml());
            //processLogics.append(new ProcessModifyXml());


            //apply process logic for each line
            do
            {

//                foreach (IProcessLogic* processLogic, processLogics)
//                {
//                    processLogic->processFile(line);
//                }














//                QStringList signalInfo = line.split(',');
//                if(signalInfo.size() == 2)
//                {
//                    std::string oldName = signalInfo.first().trimmed().toStdString();
//                    std::string newName = signalInfo.last().trimmed().toStdString();


//                    walker.setSigInfo(oldName, newName);
//                    //walk through the tree recursively
//                    //xml_tree_walker* walker =  new signal_walker();   //inheritance in cpp in private by default
//                    doc.traverse(walker);
//                }











                if(!line.contains("<"))
                {
                    lineNumber++;
                }







                line = in.readLine();

            }while(!line.isNull());

        }
        //doc.save_file(outputXml.c_str());
        //std::cout << "doc saved." << std::endl;
        qDebug()<< "total:" << lineNumber << endl;
        file.close();
    }else{
        qDebug() << file.error() << endl;
        qDebug() << file.errorString();
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}
