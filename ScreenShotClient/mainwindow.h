#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMutex>
#include <QMutexLocker>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QUdpSocket* m_udpSocket;
    QPushButton* m_requestImage;
    QLabel* m_imageAreaLabel;
    QLineEdit* m_imageAreaValue;
    QLabel* m_imageLabel;

    QByteArray m_completeImageData;
    QMutex m_mutex;
    void initializeClient();
    void handleImageRequest();
    void readPendingDatagrams();
    void showReceivedImage(QByteArray imageBytes);

};
#endif // MAINWINDOW_H
