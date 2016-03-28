TEMPLATE = lib

TARGET = TaskParseHDD

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += \
    src/parseHdd.cpp

HEADERS += \
    src/parseHdd.h
