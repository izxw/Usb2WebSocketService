include(ConsoleService.pri)

QT += core websockets serialport
QT -= gui

TARGET = UsbMonitor
CONFIG += c++11 console
CONFIG -= app_bundle
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR = $$PWD/$$PROJ_SPEC

SOURCES += \
        main.cpp \
        usbmonitor.cpp \
        webservice.cpp \
        winservice.cpp

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    dlog.h \
    lusb0_usb.h \
    usbmonitor.h \
    webservice.h \
    winservice.h

DISTFILES += \
    ConsoleService.pri

include(qtservice/qtservice.pri)



win32: LIBS += -L$$PWD/./ -lusb

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.
