TEMPLATE = app

TARGET = coex

DESTDIR = ../bin

INCLUDEPATH += ../include/

SOURCES += src/coex.cpp \
		   src/helpers.cpp

HEADERS += src/helpers.h

OBJECTS_DIR = tmp/

QT += core \
 xml \
 script \
 gui \
 xmlpatterns
