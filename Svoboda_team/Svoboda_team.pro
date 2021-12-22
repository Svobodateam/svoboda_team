#-------------------------------------------------
#
# Project created by QtCreator 2021-12-20T22:08:21
#
#-------------------------------------------------

QT       += core gui sql testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Svoboda_team
TEMPLATE = app


SOURCES += main.cpp\
    apptests.cpp \
        mainwindow.cpp \
    dbmanager.cpp

HEADERS  += mainwindow.h \
    apptests.h \
    dbmanager.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
