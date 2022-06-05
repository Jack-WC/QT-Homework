#-------------------------------------------------
#
# Project created by QtCreator 2022-05-18T19:15:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pick.cpp \
    fail.cpp \
    startscreen.cpp \
    player.cpp

HEADERS  += mainwindow.h \
    pick.h \
    fail.h \
    startscreen.h \
    player.h

FORMS    += mainwindow.ui \
    pick.ui \
    fail.ui \
    startscreen.ui

RESOURCES += \
    image.qrc \
    data.qrc
