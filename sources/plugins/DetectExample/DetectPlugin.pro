TEMPLATE = lib

TARGET = DetectExample

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/detectOS_example.cpp

HEADERS += src/detectOS_example.h
