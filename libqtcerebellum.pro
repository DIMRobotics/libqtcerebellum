#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T22:04:01
#
#-------------------------------------------------

QT       -= gui

TARGET = libqtcerebellum
TEMPLATE = lib

DEFINES += QTCEREBELLUM_LIBRARY

SOURCES += libqtcerebellum.cpp \
    message.cpp

HEADERS += libqtcerebellum.h\
        libqtcerebellum_global.h \
    message.h

unix {
    target.path = /usr/local/lib
    INSTALLS += target
}
