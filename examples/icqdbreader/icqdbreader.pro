QT       += core
QT       -= gui

TARGET = icqdbreader
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp
INCLUDEPATH += \
	../../sources/libs/qdbf/src/

unix:!macx:!symbian: LIBS += -L$$PWD/../../bin/libs/ -lqdbf

INCLUDEPATH += $$PWD/../../sources/libs/qdbf/src
DEPENDPATH += $$PWD/../../sources/libs/qdbf/src
