TEMPLATE = lib

TARGET = DetectKernel32Win

DESTDIR = ../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/detectOS.cpp

HEADERS += src/detectOS.h
