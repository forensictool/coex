TEMPLATE = lib

TARGET = TaskViber

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

QT += sql

CONFIG += dll

SOURCES += src/taskViber.cpp \

HEADERS += src/taskViber.h \
