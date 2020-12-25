#-------------------------------------------------
#
# Project created by QtCreator 2020-12-07T09:53:28
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = execution
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    iprocesslogic.cpp \
    processnewsignal.cpp \
    processchangexml.cpp \
    nodeiterator.cpp

HEADERS  += mainwindow.h \
    iprocesslogic.h \
    processnewsignal.h \
    processchangexml.h \
    nodeiterator.h

FORMS    += mainwindow.ui
