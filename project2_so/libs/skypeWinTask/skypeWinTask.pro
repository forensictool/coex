TEMPLATE = lib

DESTDIR = ../../bin/libs

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui
QT += sql

CONFIG += dll

SOURCES += src/skypeWinTask.cpp

HEADERS += src/skypeWinTask.h
