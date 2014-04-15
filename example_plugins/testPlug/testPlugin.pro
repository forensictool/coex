QT += core \
 xml \
 script \
 xmlpatterns
 
TEMPLATE = lib
TARGET = testPlugin
DESTDIR = ../bin/
SOURCES += src/testPlugin.cpp
HEADERS += src/testPlugin.h \
			../interfaces/myinterface.h
