TEMPLATE = lib

TARGET = TaskExample

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/taskExample.cpp

HEADERS += src/taskExample.h
