#-------------------------------------------------
#
# Project created by QtCreator 2016-05-04T10:26:14
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = VDL
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    vdltwo.cpp \
    demod.cpp \
    vdlthree.cpp \
    bitoperations.cpp \
    decoder.cpp \
    output.cpp \
    vdlmanager.cpp

HEADERS += \
    vdltwo.h \
    demod.h \
    vdlthree.h \
    rs.h \
    bitoperations.h \
    decoder.h \
    output.h \
    vdlmanager.h

QMAKE_CXXFLAGS += -std=c++0x


