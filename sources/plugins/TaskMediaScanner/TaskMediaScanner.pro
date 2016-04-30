TEMPLATE = lib

TARGET = TaskMediaScanner

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui
QT += sql

CONFIG += dll

SOURCES += src/taskmediascanner.cpp \
	  ../../include/hdd.cpp

HEADERS += src/taskmediascanner.h \
	  ../../include/hdd.h