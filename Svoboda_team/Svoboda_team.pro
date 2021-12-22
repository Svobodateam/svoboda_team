#-------------------------------------------------
#
# Project created by QtCreator 2021-12-20T22:08:21
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

test {
    TARGET = Svoboda_team_test
    QT += testlib
    SOURCES +=\
        apptests.cpp \
        dbmanager.cpp
    HEADERS += apptests.h dbmanager.h
}

app {
    TARGET = Svoboda_team
    SOURCES +=\
    main.cpp \
            mainwindow.cpp \
        dbmanager.cpp

    HEADERS  += mainwindow.h \
        dbmanager.h

    FORMS    += mainwindow.ui

    RESOURCES += \
        res.qrc
}

