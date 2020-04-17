#ifndef USBMONITOR_H
#define USBMONITOR_H

#ifdef QT_NO_DEBUG
#define MY_VID 0x8888
#define MY_PID 0x6019

#define EP_IN 0x81
#define EP_OUT 0x01
#else
#define MY_VID 0x1EAB
#define MY_PID 0x8303

// Device endpoint 2
#define EP_IN 0x84
#define EP_OUT 0x03
#endif
#define MY_CONFIG 1
#define MY_INTF 0

// Device of bytes to transfer.
#define BUF_SIZE 16

#include <QObject>
#include <QThread>
#include "lusb0_usb.h"
#include <QDebug>
#include <QMutex>
#include <QSettings>

class UsbMonitor : public QObject
{
    Q_OBJECT
public:
    explicit UsbMonitor(QObject *parent = nullptr);
    ~UsbMonitor();

signals:
    void message(const QString& msg);
    void finish();

public slots:
    void startScan(const QString& info);
    void stopImmediately();

private:
    QString m_msg;
    struct usb_bus *bus;
    struct usb_device *dev;
    usb_dev_handle *handler;

    QMutex m_lock;
    bool m_isCanRun;
    quint32 M_VID;
    quint32 M_PID;
    quint32 M_EP_IN;
};

#endif // USBMONITOR_H
