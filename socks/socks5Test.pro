#-------------------------------------------------
#
# Project created by QtCreator 2014-09-04T20:35:55
#
#-------------------------------------------------

QT       += core

QT       -= gui

QMAKE_MAC_SDK = macosx10.9
TARGET = socks5Test
CONFIG   += console
CONFIG   -= app_bundle
QT += network

TEMPLATE = app


SOURCES += main.cpp \
    serverthread.cpp \
    server.cpp \
    sockdateturnel.cpp

HEADERS += \
    serverthread.h \
    server.h \
    sockdateturnel.h
