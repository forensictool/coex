TEMPLATE = lib

DESTDIR = ../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/pidginWinTask.cpp

HEADERS += src/pidginWinTask.h
