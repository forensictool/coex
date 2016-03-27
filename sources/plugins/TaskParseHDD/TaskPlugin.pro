TEMPLATE = lib

TARGET = TaskParseHDD

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += \
    src/scanHdd.cpp

HEADERS += \
    src/parseHdd.h
