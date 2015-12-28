#-------------------------------------------------
#
# Project created by QtCreator 2015-12-25T22:57:14
#
#-------------------------------------------------
include(3rdparty/qtxlsx/src/xlsx/qtxlsx.pri)
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = timetable
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
