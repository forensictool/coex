TEMPLATE = lib

DESTDIR = ../../bin/libs

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/detectOS.cpp

HEADERS += src/detectOS.h
