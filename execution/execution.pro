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
    nodeiterator.cpp \
    pugixml/mainfunc.cpp \
    pugixml/pugixml.cpp \
    pugixml/signal_walker.cpp \
    processmodifyxml.cpp

HEADERS  += mainwindow.h \
    iprocesslogic.h \
    processnewsignal.h \
    nodeiterator.h \
    pugixml/pugiconfig.hpp \
    pugixml/pugixml.hpp \
    pugixml/signal_walker.h \
    processmodifyxml.h

FORMS    += mainwindow.ui
