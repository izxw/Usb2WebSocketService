include(ConsoleService.pri)

QT += core websockets serialport
QT -= gui

TARGET = myservice
CONFIG += c++11 console
CONFIG -= app_bundle
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = $$PWD/$$PROJ_SPEC

SOURCES += \
        main.cpp \
        webservice.cpp \
        winservice.cpp

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    dlog.h \
    webservice.h \
    winservice.h

DISTFILES += \
    ConsoleService.pri

include(qtservice/qtservice.pri)


