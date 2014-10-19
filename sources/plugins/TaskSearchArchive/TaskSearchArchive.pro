TEMPLATE = lib

TARGET = TaskSearchArchive

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/taskSearchArchive.cpp \
           src/writerXML.cpp

HEADERS += src/taskSearchArchive.h \
    src/writerXML.h
