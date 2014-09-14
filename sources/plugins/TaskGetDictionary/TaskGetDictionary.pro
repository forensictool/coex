TEMPLATE = lib

TARGET = TaskGetDictionary

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/taskGetDictionary.cpp

HEADERS += src/taskGetDictionary.h
