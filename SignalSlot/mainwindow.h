#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QThread>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void mainTask();
    void subTask1();
    void subTask2();
    void subTask3();
    void objectiveTask();

private:
    Ui::MainWindow *ui;
    QTimer* mainTaskTimer;
    QTimer* subTask1Timer;
    QTimer* subTask2Timer;
    QTimer* subTask3Timer;
    QTimer* objectiveTaskTimer;
};

#endif // MAINWINDOW_H
