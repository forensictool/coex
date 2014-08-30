QT += core \
 xml \
 script \
 gui \
 xmlpatterns

TARGET = mainapp
TEMPLATE = app
DESTDIR = ../bin/
SOURCES += src/main.cpp
HEADERS +=  \
			../interfaces/myinterface.h
