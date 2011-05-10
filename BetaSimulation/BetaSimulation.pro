#-------------------------------------------------
#
# Project created by QtCreator 2011-05-09T12:44:15
#
#-------------------------------------------------

QT       += core gui

TARGET = BetaSimulation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    abstractca.cpp \
    abstractstate.cpp \
    eca50.cpp \
    onedimensionstate.cpp \
    abstract1dca.cpp

HEADERS  += mainwindow.h \
    abstractca.h \
    abstractstate.h \
    eca50.h \
    onedimensionstate.h \
    abstract1dca.h

FORMS    += mainwindow.ui
