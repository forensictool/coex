TEMPLATE = lib

TARGET = TaskChromeWin

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += \     
	src/taskChromeWin.cpp

HEADERS += \
        src/taskChromeWin.h
