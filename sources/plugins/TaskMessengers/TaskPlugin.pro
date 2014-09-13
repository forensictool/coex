TEMPLATE = lib

TARGET = TaskMessengers

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/taskMessengers.cpp

HEADERS += src/taskMessengers.h
