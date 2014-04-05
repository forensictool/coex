QT       += core gui

TARGET = testPlugin
TEMPLATE = lib
CONFIG += plugin
DESTDIR = ../bin/
SOURCES += src/testPlugin.cpp
HEADERS += src/testPlugin.h \
			../interfaces/myinterface.h
