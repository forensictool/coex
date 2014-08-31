TEMPLATE = app

TARGET = coex

DESTDIR = ../../bin

INCLUDEPATH += ../include/

SOURCES += src/coex.cpp \
		   src/helpers.cpp \
		   src/config.cpp

HEADERS += src/helpers.h \
		   src/config.h

OBJECTS_DIR = tmp/

QT += core \
 xml \
 script \
 gui \
 xmlpatterns
