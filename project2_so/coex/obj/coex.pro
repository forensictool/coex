TEMPLATE = app

DESTDIR = ../bin

SOURCES += ../src/main.cpp \
		   ../src/coex/coex.cpp

HEADERS += ../src/coex/coex.h

QT += core \
 xml \
 script \
 gui \
 xmlpatterns
