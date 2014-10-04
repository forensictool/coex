TEMPLATE = lib

TARGET = TaskSearchArchive

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/taskSearchArchive.cpp

HEADERS += src/taskSearchArchive.h
