#-------------------------------------------------
#
# Project created by QtCreator 2022-05-18T19:15:20
#
#-------------------------------------------------

QT       += core gui
QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    pick.cpp \
    startscreen.cpp \
    player.cpp \
    op.cpp \
    game.cpp \
    mainframe.cpp \
    hpbar.cpp \
    musiclevel.cpp \
    levelpick.cpp \
    playwindow.cpp

HEADERS  += mainwindow.h \
    pick.h \
    startscreen.h \
    player.h \
    op.h \
    game.h \
    mainframe.h \
    hpbar.h \
    musiclevel.h \
    levelpick.h \
    playwindow.h

FORMS    += mainwindow.ui \
    pick.ui \
    startscreen.ui \
    op.ui \
    game.ui \
    mainframe.ui \
    musiclevel.ui \
    levelpick.ui \
    playwindow.ui

RESOURCES += \
    image.qrc \
    data.qrc
