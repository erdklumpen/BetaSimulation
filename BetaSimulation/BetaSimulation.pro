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
    eca.cpp \
    ecasettings.cpp \
    cahistory.cpp \
    plotdensitydialog.cpp \
    twodimensionstate.cpp \
    abstract2dca.cpp \
    gameoflife.cpp

HEADERS  += mainwindow.h \
    abstractca.h \
    abstractstate.h \
    onedimensionstate.h \
    abstract1dca.h \
    automatasettings.h \
    eca.h \
    ecasettings.h \
    cahistory.h \
    plotdensitydialog.h \
    twodimensionstate.h \
    abstract2dca.h \
    gameoflife.h

FORMS    += mainwindow.ui \
    automatasettings.ui \
    ecasettings.ui \
    plotdensitydialog.ui
