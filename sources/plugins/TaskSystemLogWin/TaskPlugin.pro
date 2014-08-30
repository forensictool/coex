TEMPLATE = lib

TARGET = TaskWinSysLog

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/winSysLog.cpp

HEADERS += src/winSysLog.h
