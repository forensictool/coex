TEMPLATE = lib

TARGET = TaskFirefoxWin

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += \
    src/taskFirefox.cpp

HEADERS += \
    src/taskFirefox.h
