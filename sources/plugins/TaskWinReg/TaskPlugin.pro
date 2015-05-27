TEMPLATE = lib

TARGET = TaskOutlook2007

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += \
           src/writerMessages.cpp \
    src/WinReg.cpp


HEADERS += \
           src/writerMessages.h \
    src/taskWinReg.h
