#-------------------------------------------------
#
# Project created by QtCreator 2023-05-29T23:20:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia multimediawidgets

TARGET = blackjack
TEMPLATE = app


SOURCES += main.cpp\
       card.cpp\
       mainwindow.cpp

HEADERS  += mainwindow.h \
    card.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc


