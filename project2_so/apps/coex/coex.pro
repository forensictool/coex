TEMPLATE = app

DESTDIR = ../../bin

INCLUDEPATH += ../../include/

SOURCES += src/main.cpp \
		   src/coex.cpp

HEADERS += src/coex.h

OBJECTS_DIR = tmp/

QT += core \
 xml \
 script \
 gui \
 xmlpatterns
