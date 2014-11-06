TEMPLATE = lib

TARGET = TaskSearchArchive

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES += src/taskSearchArchive.cpp \
           src/writerXML.cpp \
           src/qzip.cpp

HEADERS += src/taskSearchArchive.h \
           src/qzipreader_p.h \
           src/writerXML.h \
           src/qzipwriter_p.h
