TEMPLATE = lib

TARGET = TaskWinReg

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/main.cpp

HEADERS += src/header.h
