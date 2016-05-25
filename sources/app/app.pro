TEMPLATE = app

TARGET = coex

DESTDIR = ../../bin

INCLUDEPATH += ../include/

SOURCES += src/coex.cpp \
		   src/helpers.cpp \
		   src/config.cpp \
		   ../include/hdd.cpp

HEADERS += src/helpers.h \
		   src/config.h \
		../include/hdd.h

OBJECTS_DIR = tmp/

QT += core \
 xml \
 script \
 gui \
 xmlpatterns
