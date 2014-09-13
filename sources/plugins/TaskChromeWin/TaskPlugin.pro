TEMPLATE = lib

TARGET = TaskChromeWin

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/task.cpp

HEADERS += src/task.h
