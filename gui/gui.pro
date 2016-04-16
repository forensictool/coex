#-------------------------------------------------
#
# Project created by QtCreator 2016-04-07T14:56:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUIv2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    about.cpp \
    settings.cpp \
    messagedone.cpp

HEADERS  += mainwindow.h \
    about.h \
    settings.h \
    messagedone.h

FORMS    += mainwindow.ui \
    about.ui \
    settings.ui \
    messagedone.ui

RESOURCES += \
    resource/icons.qrc
