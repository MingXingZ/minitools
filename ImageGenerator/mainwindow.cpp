#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QPainter>
#include <QLabel>
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QImage image(200, 80, QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&image);
    painter.fillRect(image.rect(), Qt::yellow);
    painter.drawText(image.rect(), Qt::AlignCenter | Qt::AlignVCenter, "Bad Request\nscreen size:(800, 600)\n  requested size:(600, 800)");
    //image.save("output.png");
    QLabel* label = new QLabel(this);// if you use a non-pointer, the image would not be shown, because the label object is destroied when this function finishes.
    //label->setPixmap(QPixmap("output.png"));
    label->setPixmap(QPixmap::fromImage(image));
    qDebug()<<image.width()<<endl;
    label->setFixedSize(image.width(), image.height());
    label->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
