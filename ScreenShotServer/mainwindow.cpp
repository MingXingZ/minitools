#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include <QApplication>
#include "qdesktopwidget.h"
#include <QBuffer>
#include <QLabel>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_maximumPacketSize = 1024 * 63;
    screenShotServer();
}


void MainWindow::screenShotServer()
{
    m_udpSocket = new QUdpSocket(this);
    QString ipAddress = getIPAddress();
    QStringList ipInfo = ipAddress.split(':');
    bool isBindSuccessful = m_udpSocket->bind(QHostAddress(ipInfo.first().trimmed()), ipInfo.last().trimmed().toInt());
    if(isBindSuccessful)
    {
        qDebug()<<"server started on "<<ipAddress<<endl;
    }else{
        qDebug()<<"failed to start the server on "<<ipAddress<<endl;
    }
    connect(m_udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

void MainWindow::readPendingDatagrams()
{
    while(m_udpSocket->hasPendingDatagrams())
    {
        QByteArray receivedData;
        QHostAddress ipAddr;
        quint16 port;
        receivedData.resize(m_udpSocket->pendingDatagramSize());
        m_udpSocket->readDatagram(receivedData.data(), receivedData.size(), &ipAddr, &port);
        //QMutexLocker locker(&m_mutex);
        QByteArray snippedImage = snipScreen(receivedData);

        //check if we get a valid screenshot
        if("bad request" == snippedImage)
        {
            m_udpSocket->writeDatagram(snippedImage, ipAddr, port);
            break;
        }

        //separate the image into multiple packets if it has a big size.
        quint64 initialSize = snippedImage.size();
        if(initialSize > m_maximumPacketSize)
        {
            int packetCount = (initialSize % m_maximumPacketSize == 0) ? (initialSize/m_maximumPacketSize) : (initialSize/m_maximumPacketSize + 1);
            for(int i=0;i<packetCount;++i)
            {
                QByteArray newPacketData = snippedImage.mid(i * m_maximumPacketSize, m_maximumPacketSize);
                m_udpSocket->writeDatagram(newPacketData, ipAddr, port);
            }
        }else{
               m_udpSocket->writeDatagram(snippedImage, ipAddr, port);
        }

        //this packet indicates the end of image data sending.
        m_udpSocket->writeDatagram(QByteArray("END"), ipAddr, port);
    }
}

QByteArray MainWindow::snipScreen(QByteArray requirements)
{
    qDebug()<<"Area required: "<<requirements<<endl;



    //validate the requirements-----begin
    QList<QByteArray> requirementArr = requirements.split(',');
    int img_x = 0, img_y = 0, img_width = 10, img_height = 10;
    if(requirementArr.size() != 4)
    {
        qDebug()<<"invalid requirements: format invalid"<<endl;
        return QByteArray("bad request-> invalid format");
    }else{
        img_x = requirementArr.at(0).toInt();
        img_y = requirementArr.at(1).toInt();
        img_width = requirementArr.at(2).toInt();
        img_height = requirementArr.at(3).toInt();
    }
    //get the whole screen
    QPixmap pixmap;
    QPixmap screen = pixmap.grabWindow(QApplication::desktop()->winId());
    if((img_width + img_x) > screen.width() || (img_height + img_y) > screen.height() || img_x < 0 || img_y < 0)
    {
        qDebug()<<"invalid requirements: size invalid"<<endl;
        QString screenSize;
        QString requestedArea;
        screenSize.sprintf("%s 0,0,%d,%d", "screen area:", screen.width(), screen.height());
        requestedArea.sprintf("%s %d,%d,%d,%d", "requested area:", img_x, img_y, img_width, img_height);
        QString badResuestString = "bad request-> "+screenSize+"    "+requestedArea;
        return QByteArray(badResuestString.toLatin1());
    }
    //validate the requirements-----end



    //get intended screen area and return it as a byte array.
    QPixmap intendedImage = screen.copy(img_x, img_y, img_width, img_height);
    qDebug()<<"screen geometry:"<<screen.width()<<":"<<screen.height()<<endl;
    qDebug()<<"intended image geometry:"<<intendedImage.width()<<":"<<intendedImage.height()<<endl;
    QByteArray byteArray = QByteArray();
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    intendedImage.save(&buffer, "png", 0);
    qDebug()<<"intended image size:"<<byteArray.size()<<endl;

    return byteArray;
}


QString MainWindow::getIPAddress()
{
    QFile ipConfigFile("./ip.config");
    if(!ipConfigFile.exists())
    {
        qDebug()<<"please provide an ip configure file named ip.config under the same foler with this app\n format: 192.168.230.115"<<endl;
    }

    bool opened = ipConfigFile.open(QIODevice::ReadOnly | QIODevice::Text);
    if(opened)
    {
        QString ipAddress;
        QTextStream in(&ipConfigFile);
        ipAddress = in.readLine();
        return ipAddress;

    }else{
        qDebug()<<"open file failed"<<endl;
        return "";
    }
}


MainWindow::~MainWindow()
{

}

