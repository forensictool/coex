TEMPLATE = lib

TARGET = treadTaskICQ

DESTDIR = ../../../bin/plugins

INCLUDEPATH += ../../include/

OBJECTS_DIR = tmp/

QT -= gui

CONFIG += dll

SOURCES +=  src/threadTaskICQ.cpp\
            src/writerMessages.cpp\
            src/XMLReader_ICQContacts.cpp \

HEADERS +=  src/threadTaskICQ.h\
            src/writerMessages.h\
            src/XMLReader_ICQContacts.h \
