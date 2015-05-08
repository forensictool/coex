TEMPLATE = lib

TARGET = TaskSearchProgram

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/taskSearchProgram.cpp \
    src/writerMessages.cpp

HEADERS += src/taskSearchProgram.h \
    src/writerMessages.h
