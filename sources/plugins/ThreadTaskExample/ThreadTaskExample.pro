TEMPLATE = lib

TARGET = ThreadTaskExample

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/threadTaskExample.cpp

HEADERS += src/threadTaskExample.h
