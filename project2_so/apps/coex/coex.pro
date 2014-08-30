TEMPLATE = app

DESTDIR = ../../bin

SOURCES += src/main.cpp \
		   src/coex/coex.cpp

INCLUDEPATH += ../../include/

HEADERS += src/coex/coex.h

OBJECTS_DIR = tmp/

QT += core \
 xml \
 script \
 gui \
 xmlpatterns
