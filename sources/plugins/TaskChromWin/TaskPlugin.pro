TEMPLATE = lib

TARGET = TaskChromWin

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui
QT += sql

CONFIG += dll

SOURCES += 	src/taskchromwin.cpp \
			src/writerxml.cpp

HEADERS += 	src/taskchromwin.h \
			src/writerxml.h
