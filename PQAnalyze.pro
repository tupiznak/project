#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PQAnalyze
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
         qcustomplot.cpp\
         CustomPlotZoom.cpp

HEADERS  += mainwindow.h\
         qcustomplot.h\
         CustomPlotZoom.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS +=-std=c++11
