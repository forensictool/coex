TEMPLATE = lib

TARGET = ImageVerifier

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += \     
    src/TaskImageVerifier.cpp

HEADERS +=  \
    src/TaskImageVerifier.h
