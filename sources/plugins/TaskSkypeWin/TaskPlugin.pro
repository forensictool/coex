TEMPLATE = lib

TARGET = TaskSkypeWin

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui
QT += sql

CONFIG += dll

SOURCES += 	src/skypeWinTask.cpp \
			src/writerMessages.cpp

HEADERS += 	src/skypeWinTask.h \
			src/writerMessages.h
