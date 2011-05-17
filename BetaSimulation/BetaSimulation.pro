#-------------------------------------------------
#
# Project created by QtCreator 2011-05-09T12:44:15
#
#-------------------------------------------------

QT       += core gui

TARGET = BetaSimulation
TEMPLATE = app

CONFIG += qwt

LIBS += -lqwt

SOURCES += main.cpp\
        mainwindow.cpp \
    abstractca.cpp \
    abstractstate.cpp \
    onedimensionstate.cpp \
    abstract1dca.cpp \
    automatasettings.cpp \
    eca.cpp

HEADERS  += mainwindow.h \
    abstractca.h \
    abstractstate.h \
    onedimensionstate.h \
    abstract1dca.h \
    automatasettings.h \
    eca.h

FORMS    += mainwindow.ui \
    automatasettings.ui
