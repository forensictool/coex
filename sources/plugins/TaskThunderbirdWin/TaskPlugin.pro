TEMPLATE = lib

TARGET = TaskThunderbirdWin

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/taskThunderbird.cpp

HEADERS += src/taskThunderbird.h
