#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = NULL);
    ~MainWindow();
    void screenShotServer();
    QByteArray snipScreen(QByteArray requirements);
public slots:
    void readPendingDatagrams();
    QString getIPAddress();

private:
    QUdpSocket* m_udpSocket;
    quint64 m_maximumPacketSize;
    QPixmap* m_currentScreen;
};
#endif // MAINWINDOW_H
