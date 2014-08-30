TEMPLATE = lib

TARGET = TaskSkypeWin

DESTDIR = ../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui
QT += sql

CONFIG += dll

SOURCES += src/skypeWinTask.cpp

HEADERS += src/skypeWinTask.h
