#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

typedef QMap<QString, QStringList> FileDepen;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool checkFile(const QString &fileName);
    bool isAlreadyExisted(QFileInfo fileInfo);
    void findFileRecur(const QString &filePath);
    void layoutDepen(QStringList projectFiles);
    void registerIncludedFiles(QStringList files);
    void sortOutHierarchy();
    QStringList getIncludeFiles(const QString& fileName);
    bool isInclude_able(QByteArray individualLine);
    bool isProjectFile(QString file);
    QString getFileNameWithoutPath(QString fileWithPath);
    void init();
private slots:
    void on_openFolder_btn_clicked();

private:
    Ui::MainWindow *ui;
    QStringList fileList;
    int rawFileSum;

    FileDepen* filesInfo = new FileDepen();
    FileDepen* dependencyHierarchy = new FileDepen();
    FileDepen* repeatedFiles = new FileDepen();
};
#endif // MAINWINDOW_H
