#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T22:04:01
#
#-------------------------------------------------

QT       -= gui

TARGET = qtcerebellum
TEMPLATE = lib

DEFINES += QTCEREBELLUM_LIBRARY

SOURCES += \
    message.cpp \
    qtcerebellum.cpp

HEADERS +=\
    message.h \
    qtcerebellum_global.h \
    qtcerebellum.h

unix {
    target.path = /usr/local/lib
    INSTALLS += target
}

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += libzmq
