#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::init()
{
    this->filesInfo->clear();
    this->dependencyHierarchy->clear();
    this->repeatedFiles->clear();
    this->fileList.clear();

}


void MainWindow::on_openFolder_btn_clicked()
{

    //we need to first initialize the system here
    init();
                                    //this can be configured to reduce steps
    QString path = QFileDialog::getExistingDirectory(this, "select folder", "./",  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(path.isEmpty())
        return;

    qDebug()<<"\t open folder:"<<path<<endl;

    QDir dir(path);
    foreach (QFileInfo fileInfo , dir.entryInfoList())
    {
        if (fileInfo.isFile()) {
            QString strFileName = fileInfo.fileName();
            if (checkFile(strFileName)) {
                if(isAlreadyExisted(fileInfo))
                    continue;//already included
                fileList << fileInfo.filePath();
            }
        }else {
            if(fileInfo.fileName() == "." || fileInfo.fileName() == ".." || fileInfo.fileName() == "tests") {
                continue;
            }

            //find files recursively.
            findFileRecur(fileInfo.absoluteFilePath());
        }
    }

    qDebug()<<"\t file number:"<<fileList.size()<<endl;
    rawFileSum = fileList.size();
    //once we get all the files, we can head on to analyze the dependency among these files.
    layoutDepen(fileList);

}

bool MainWindow::isAlreadyExisted(QFileInfo fileInf)
{
    auto res = getFileNameWithoutPath(fileInf.filePath());
    auto existedFiles = fileList.filter(res);
    if(existedFiles.size() > 0)
    {
        auto resExisted = getFileNameWithoutPath(existedFiles.first());
        if(res == resExisted)
        {
            //we need to collect these files together
            if(repeatedFiles->count(resExisted) == 0)
            {
                repeatedFiles->insert(resExisted, *(new QStringList()));
                auto value = repeatedFiles->value(resExisted);
                value.append(existedFiles.first());
                repeatedFiles->insert(resExisted, value);// we need to improve the method of updating maps
            }

            auto value = repeatedFiles->value(resExisted);
            value.append(fileInf.filePath());
            repeatedFiles->insert(resExisted, value);
//            qDebug()<<"\t repeted file: "<<fileInf.filePath();
//            qDebug()<<"\t already existed:"<<fileList.filter(res).first()<<endl;
            return true;
        }
    }
    return false;
}

void MainWindow::findFileRecur(const QString &filePath)
{
    QDir dir(filePath);
    foreach (QFileInfo fileInfo , dir.entryInfoList()) {
        if (fileInfo.isFile()) {
            QString strFileName = fileInfo.fileName();
            if (checkFile(strFileName)) {
                //get only file name, without complete path and see if it's included
                if(isAlreadyExisted(fileInfo))
                    continue;//already included
                fileList << fileInfo.filePath();
            }
        } else {
            if(fileInfo.fileName() == "." || fileInfo.fileName() == "..") {
                continue;
            }
            //find files recursively
            findFileRecur(fileInfo.absoluteFilePath());
        }
    }

    //remove files with the same name(even if their pathes are different)
    //if multiple files with the same name detected, issue a warning and print the repetitive file
}

bool MainWindow::checkFile(const QString &fileName)
{

    //configured for qt-creator project--begin
    QStringList filesNOTtoIncluded;
    filesNOTtoIncluded.append("qobjectdefs.h");
    filesNOTtoIncluded.append("qglobal.h");
    filesNOTtoIncluded.append("qconfig.h");
    filesNOTtoIncluded.append("windows.h");
    filesNOTtoIncluded.append("t.h");
    filesNOTtoIncluded.append("system1.h");
    filesNOTtoIncluded.append("sqlite3.c");

    if(filesNOTtoIncluded.contains(fileName))
        return false;
    //configured for qt-creator project--end


    if (fileName.startsWith("moc_") || fileName.startsWith("ui_") || fileName.startsWith("qrc_")) {
        return false;
    }
    QFileInfo file(fileName);
    QString suffix = "*." + file.suffix();
    QString filter = ui->fileFormat->text().trimmed();
    QStringList filters = filter.split(" ");
    return filters.contains(suffix);
}

void MainWindow::layoutDepen(QStringList projectFiles)
{
    registerIncludedFiles(projectFiles);
    sortOutHierarchy();
}


//add sorted files to the filesInfo map
void MainWindow::registerIncludedFiles(QStringList files)
{
    foreach(QString file, files)
    {
       // qDebug()<<"\t"<<file<<":"<<endl;
        filesInfo->insert(file, getIncludeFiles(file));
        //qDebug()<<"\n\n\n";
    }
}

#include<algorithm>
//we need to analyze the files recursively,
void MainWindow::sortOutHierarchy()
{
    int level = 0;

    while((filesInfo->size() > 0))
    {
        QStringList sl;
        QString levelPre;
        if(level < 10)
        {
            levelPre = "level_000";
        }else if(level >= 10 && level < 100)
        {
            levelPre = "level_00";
        }else if(level >=100 && level < 1000)
        {
            levelPre = "level_0";
        }else{
            levelPre = "level_";
        }
        QString fileLevel = levelPre+QString::number(level, 10);//need to be improved to enable printing alphabatically.
        dependencyHierarchy->insert(fileLevel, sl);

        foreach(auto key, filesInfo->keys())
        {
            QStringList includedFiles = filesInfo->value(key);
            if(includedFiles.size() == 0)
            {
                auto res = key.split('/');
                QString temp = res.last();
                sl.append(temp);//the naming of file, this point needs to be further refined
                filesInfo->remove(key);
            }
        }
        dependencyHierarchy->insert(fileLevel, sl);//it's not referenced by address, we need to reasign the value

        //look up the file and see if lower level files are included, if it is, then remove them from file include list

        foreach(auto key, filesInfo->keys())
        {
            QStringList includedFiles = filesInfo->value(key);
            QStringList lowerFiles = dependencyHierarchy->value(fileLevel);
            foreach(QString lowerFile, lowerFiles)
            {
                if(includedFiles.contains(lowerFile))
                {
                    int index = includedFiles.indexOf(lowerFile);
                    includedFiles.removeAt(index);
                }
            }
            filesInfo->insert(key, includedFiles);
        }

        if(level > 6000)   //todo: log info to info file automatically(maybe within the project, txt format)  you can also present the info in a QT GUI app, container is easy to implement this.
        {
            qDebug()<<"\t warning: problem detected!!!!!!!!!!!!!!!!!";
            break;
        }
        level++;

    }

    int resultFileSum = 0;


    //now its time to print out the resulting hierarchy
//    foreach(auto key, dependencyHierarchy->keys())//this will cause unintended results,0...9, 10, 11 will be printed first
//    {
//        int individualSize = dependencyHierarchy->value(key).size();
//        if(individualSize == 0)
//            continue;
//        resultFileSum += individualSize;
//        qDebug()<<"\t"<<key<<":"<<"(size-"<<individualSize<<")"<<endl;
//        foreach(auto file, dependencyHierarchy->value(key))
//        {
//            qDebug()<<"\t"<<file;
//        }
//        qDebug()<<"\n\n\n";
//    }


    QStringList allFiles;
    for(auto iter = dependencyHierarchy->begin(); iter != dependencyHierarchy->end(); ++iter)
    {
        int individualSize = dependencyHierarchy->value(iter.key()).size();
        if(individualSize == 0)
            continue;
        resultFileSum += individualSize;
        qDebug()<<"\t"<<iter.key()<<":"<<"(size-"<<individualSize<<")"<<endl;
        QMap<QString, int> outputHelper;
        int mapInt = 0;
        foreach(auto file, dependencyHierarchy->value(iter.key()))
        {
            outputHelper.insert(file, mapInt);
        }
        //now we can use keys method of map to output included files alphabatically.
        foreach(auto key, outputHelper.keys())
        {
//            bool isSkip = false;
//            if(key.endsWith(".cpp") || key.endsWith(".c"))
//            {
//                if(allFiles.contains(key.split('.').at(0)+".h"))
//                {
//                      isSkip = true;
//                }
//            }
//            if(!isSkip)
            qDebug()<<"\t"<<key;   //if we can print its path at the end of each file name, it's easier to look it up(how the intellisense work)

            allFiles.append(key);

        }


        qDebug()<<"\n\n\n";
    }

    qDebug()<<"\t number of files included in analysis:"<<rawFileSum;
    qDebug()<<"\t number of hierarchy files:"<<resultFileSum;


    //print repeated files

    int repeatedFilesSum = 0;
    foreach(auto key, repeatedFiles->keys())
    {
        int individualSize = repeatedFiles->value(key).size();
        repeatedFilesSum += individualSize;
        qDebug()<<"\t"<<key<<" repeated:";
        foreach(auto file, repeatedFiles->value(key))
        {
            qDebug()<<"\t"<<file;
        }
        qDebug()<<"\n\n";
    }

    repeatedFilesSum -= repeatedFiles->count();
    qDebug()<<"\t number of repeated files:"<<repeatedFilesSum;
    qDebug()<<"\t number of project file:"<<repeatedFilesSum+rawFileSum;








    //the next step is to figure out all the dependency modules, from top to bottom...need to be presented in a tree manner
    //the current analysis result is for bottom-to-up understanding of a project (understanding a system systematically) (you soon get bored with this approach,
    //because to make sense an entity, knowing what it is isn't enough. you also need to know how it's used, its role within a system(context)
    //it lacks a sense of purpose compared to understanding a project from top to bottom. (quickly figure out a certain piece of logic)
    //but if you read code from the bottom, it's very likely that you do not need to jump too much from file to file, which is a typical thing when reading from the top(when the project is relatively large)
    //and,  it's beneficial to understand each element thoroughly, step by step, and review constantly(review level0 when you finished it, and then do the same with level 1, and so on).
    //so that you avoid later jump back when viewing higher level components. and you also know where to look
    //at,or where to find what you need, roughly.
    //for project, you will quickly find how it is used, because it's included one level up the hierarchy(or it's used independently).(might not be one level)
    //so reading project is the most efficient method to learn. the same rule applies to other similar learning--now I see the benefits of btt.
    //we need a banlanced between these two approaches.
    //I prefer the latter, currently. maybe we need to redefine what "dependent" means.
    //btt works better if you understand and remember the lower layer(how to understand and remember? how it's used)
    //learn what you need.  but for projects within a company, every basic element is worth learning. it's not that big.   now I feel that the bottom-to-top approach is certainly not bad.
    //you also need to know how to understand a piece of logic quickly.(this is a common scenario when it comes to debugging.)
}

bool MainWindow::isInclude_able(QByteArray individualLine)
{
    if(individualLine.contains("include") && individualLine.contains("#") && !(individualLine.contains("/*")) && (individualLine.trimmed().at(0) == '#'))
        return true;
    return false;

}

//get included files for each file in this project
QStringList MainWindow::getIncludeFiles(const QString& fileName)
{
    QStringList filesIncluded;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        goto END;
    while(!file.atEnd())  //you can choose to delete certain contents to remove noise like comment for higher accuracy....//you can even modify,add content to enable more effective parser
    {                                                                                                          //sometimes you have to do this.(the include logic is difficult to figure out)
        QByteArray line = file.readLine();
        if(isInclude_able(line))   //it's very complicated, especially for large projects, we need to deal with the logic separately.
        {
            QString resultFile = "";
            QList<QByteArray> res;
            if(line.contains("<") && line.contains(">"))
            {
                res = line.split('<');
                if(res.size() < 2)
                    continue;
                resultFile = res.at(1).split('>').at(0);
            }else
            {
                res = line.split('"');
                if(res.size() < 2)
                    continue;
                 resultFile = res.at(1);
            }


            if(resultFile.split('/').size() > 1)
            {
                resultFile = resultFile.split('/').last();
            }

            //decide if the file is within the project
            if(!isProjectFile(resultFile))
                continue;

            if(filesIncluded.contains(resultFile))
            {
                //qDebug()<<"\t include file repeatedly:"<<resultFile<<"within file"<<fileName<<endl;
                continue;
            }

            filesIncluded.append(resultFile);
            //qDebug()<<"\t"<<res.at(1)<<endl;
        }
    }
    END:
    return filesIncluded;
}


bool MainWindow::isProjectFile(QString file)
{
    foreach(QString fileItem, fileList)
    {
        auto resShortName = getFileNameWithoutPath(fileItem);
        //if(fileItem.contains(file) && (file.contains(".h") || file.contains(".c")))  //what if a header file has no suffix
        if(file == resShortName)
        {
            return true;
        }
    }
   return false;
}

//if I can get the complete path of the included files, then this method is not needed(the intellisense knows this info)
QString MainWindow::getFileNameWithoutPath(QString fileWithPath)
{
    auto res = fileWithPath.split('/');
    return res.last();
}
