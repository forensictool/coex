TEMPLATE = lib

TARGET = TaskOutlook2007

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/taskOutlook.cpp \
           src/writerAddress.cpp


HEADERS += src/taskOutlook.h \
           src/writerAddress.h
