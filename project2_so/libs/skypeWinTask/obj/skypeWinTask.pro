TEMPLATE = lib

DESTDIR = ../../../apps/coex/bin/libs

QT -= gui
QT += sql

CONFIG += dll

SOURCES += ../src/skypeWinTask.cpp

HEADERS += ../src/skypeWinTask.h