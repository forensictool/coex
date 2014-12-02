
TARGET = QDbf

# include(library.pri)
TEMPLATE = lib
DEFINES += QDBF_LIBRARY

DESTDIR = obj
TARGET = ../../../../bin/libs/qdbf
CONFIG += dll

OBJECTS_DIR = obj
    MOC_DIR = obj
BUILD_PATH = obj

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
