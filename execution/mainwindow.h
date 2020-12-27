#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "processnewsignal.h"
#include <QList>
#include "processmodifyxml.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<IProcessLogic*> processLogics;
    ProcessModifyXml proXml;
    signal_walker walker;
};

#endif // MAINWINDOW_H
