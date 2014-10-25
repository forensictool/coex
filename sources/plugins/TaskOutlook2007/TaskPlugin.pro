TEMPLATE = lib

TARGET = TaskOutlook2007

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/taskOutlook2007.cpp \
           src/writerMessages.cpp


HEADERS += src/taskOutlook2007.h \
           src/writerMessages.h
