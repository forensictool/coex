TARGET = QDbf

TEMPLATE = lib
DEFINES += QDBF_LIBRARY

DESTDIR = tmp/
TARGET = ../../../../bin/libs/qdbf
CONFIG += dll

OBJECTS_DIR = tmp/
    MOC_DIR = tmp/
BUILD_PATH = tmp/

INCLUDEPATH += $$PWD
DEPENDPATH += $$INCLUDEPATH

SOURCES += \
    src/qdbffield.cpp \
    src/qdbfrecord.cpp \
    src/qdbftable.cpp \
    src/qdbftablemodel.cpp
HEADERS += \
    src/qdbffield.h \
    src/qdbfrecord.h \
    src/qdbftable.h \
    src/qdbftablemodel.h \
    src/qdbf_global.h
