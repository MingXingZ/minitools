#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_completeImageData.resize(0);
    initializeClient();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initializeClient()
{

    m_imageLabel = new QLabel(NULL);
    //m_imageLabel->setGeometry(this->width()/2 -100, 60);
    m_imageLabel->move(20, 80);
    m_imageAreaLabel = new QLabel("image area(x,y,width,height):", this);
    m_imageAreaLabel->setGeometry(this->width()/2 - 150, 0, 300, 30);
    m_imageAreaValue = new QLineEdit("0,0,400,400", this);//add value check later
    m_imageAreaValue->setGeometry(this->width()/2 + 25, 5, 200, 20);
    m_requestImage = new QPushButton("request a screenshot", this);
    m_requestImage->setGeometry(this->width()/2 - 100, 45, 200, 30);
    connect(m_requestImage, &QPushButton::clicked, this, &MainWindow::handleImageRequest);
    m_udpSocket = new QUdpSocket();
    m_udpSocket->bind(QHostAddress("127.0.0.1"), 22221);
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &MainWindow::readPendingDatagrams);
}
void MainWindow::handleImageRequest()
{
    QString coordinateValue = this->m_imageAreaValue->text();
    QByteArray coordinatesArray;
    coordinatesArray.append(coordinateValue);
    m_udpSocket->writeDatagram(coordinatesArray, coordinatesArray.size(), QHostAddress("127.0.0.1"), 33333);
}
void MainWindow::readPendingDatagrams()
{
    while(m_udpSocket->hasPendingDatagrams())
    {
        //QMutexLocker locker(&m_mutex);
        QByteArray receivedData;
        QHostAddress ipAddr;
        quint16 port;
        receivedData.resize(m_udpSocket->pendingDatagramSize());
        m_udpSocket->readDatagram(receivedData.data(), receivedData.size(), &ipAddr, &port);
        showReceivedImage(receivedData);
    }
}
void MainWindow::showReceivedImage(QByteArray imageBytes)
{
    if(imageBytes.contains("bad request"))
    {
        QString info = imageBytes;
        qDebug()<<info<<endl;
        return;
    }

    if(imageBytes == "END")
    {
        QPixmap imagePixmap;
        imagePixmap.loadFromData(m_completeImageData, "png");
        //imagePixmap.save("c:\\dev\\test1.png", "png", 100);
        m_imageLabel->setPixmap(imagePixmap);
        //m_imageLabel->setParent(this);
        m_imageLabel->setFixedSize(imagePixmap.width(), imagePixmap.height());
        m_imageLabel->show();
        this->update();
        m_completeImageData.resize(0);
    }else{
        m_completeImageData.append(imageBytes);
    }
}
