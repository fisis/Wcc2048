#-------------------------------------------------
#
# Project created by QtCreator 2014-03-11T13:19:13
#
#-------------------------------------------------

QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Wcc2048
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra

SOURCES += main.cpp\
        gui/mainwindow.cpp \
    core/tile.cpp \
    core/board.cpp \
    core/game.cpp \
    gui/qgameboard.cpp \
    gui/qtile.cpp \
    gui/qresetbutton.cpp \
    core/observer.cpp \
    core/subject.cpp \
    gui/qgameoverwindow.cpp \
    webcamcap.cpp

HEADERS  += gui/mainwindow.h \
    core/tile.h \
    core/board.h \
    core/game.h \
    gui/qgameboard.h \
    gui/qtile.h \
    gui/qresetbutton.h \
    core/observer.h \
    core/subject.h \
    gui/qgameoverwindow.h \
    webcamcap.h

FORMS += \
    mainwindow.ui

