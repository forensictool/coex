TEMPLATE = lib

TARGET = TaskFirefoxWin

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui
QT += sql

CONFIG += dll

SOURCES += src/taskFirefox.cpp \
			src/xml.cpp

HEADERS += src/taskFirefox.h \
			src/xml.h
