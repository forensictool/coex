TEMPLATE = lib

TARGET = TaskPidginWin

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += 	src/pidginWinTask.cpp \
			src/writerMessages.cpp

HEADERS += 	src/pidginWinTask.h \
			src/writerMessages.h
