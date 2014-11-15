TEMPLATE = lib

TARGET = TaskMessengers

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES +=  src/taskMessengers.cpp\
            src/writerMessages.cpp\
            src/XMLReader_ICQContacts.cpp \

HEADERS +=  src/taskMessengers.h\
            src/writerMessages.h\
            src/XMLReader_ICQContacts.h \
