TEMPLATE = lib

DESTDIR = ../../bin/libs

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/pidginWinTask.cpp

HEADERS += src/pidginWinTask.h
