TEMPLATE = lib

TARGET = TaskGetDictionary

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT += core sql

QT -= gui

CONFIG += dll

SOURCES += src/taskGetDictionary.cpp \
           src/coexDb.cpp

HEADERS += src/taskGetDictionary.h \
           src/coexDb.h
