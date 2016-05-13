#-------------------------------------------------
#
# Project created by QtCreator 2016-04-01T23:52:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rAstrogui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    drawingarea.cpp \
    dialognew.cpp \
    savefile.cpp

HEADERS  += mainwindow.h \
    drawingarea.h \
    dialognew.h \
    savefile.h

FORMS    += mainwindow.ui \
    dialognew.ui \
    savefile.ui
