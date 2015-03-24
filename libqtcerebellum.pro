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
    qtcerebellum.cpp \
    msgtypes.cpp

INCLUDEPATH += ./include

HEADERS +=\
    include/QCerebellum/message.h \
    include/QCerebellum/msgtypes.h \
    include/QCerebellum/qtcerebellum.h \
    include/QCerebellum/qtcerebellum_global.h

unix {
    target.path = /usr/local/lib
    INSTALLS += target
}

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += libzmq
