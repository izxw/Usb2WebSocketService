#include "usbmonitor.h"

UsbMonitor::UsbMonitor(QObject *parent) : QObject(parent)
{
    m_isCanRun = true;
    usb_init(); /* initialize the library */
    usb_find_busses(); /* find all busses */
    usb_find_devices(); /* find all connected devices */

    QSettings settings(QSettings::IniFormat,QSettings::SystemScope,"NXPOST SOFT","UsbMonitor");

    M_VID = settings.value("USB_VID").toInt();
    M_PID = settings.value("USB_PID").toInt();
    qDebug() << M_VID << M_PID;
    M_EP_IN = settings.value("USB_EP_IN").toInt();


    for(bus = usb_get_busses(); bus; bus = bus->next) {
        for(dev = bus->devices; dev; dev = dev->next) {
            if((dev->descriptor.idVendor == M_VID) && (dev->descriptor.idProduct == M_PID)) {
                handler = usb_open(dev);
            }else{
                exit(1);
            }
        }
    }

    if (usb_set_configuration(handler, MY_CONFIG) < 0) {
        qDebug("error setting config #%d: %s", MY_CONFIG, usb_strerror());
        exit(1);
    }
    if (usb_claim_interface(handler, MY_INTF) < 0) {
        qDebug("error claiming interface #%d:\n%s", MY_INTF, usb_strerror());
        exit(1);
    }
}

UsbMonitor::~UsbMonitor()
{
    qDebug() << "销毁";
}

void UsbMonitor::startScan(const QString& info)
{
    char tmp[BUF_SIZE];
    int ret;
    QMutex mutex;

    // Running a sync read test
    while(1)
    {

        ret = usb_bulk_read(handler, M_EP_IN, tmp, sizeof(tmp), 5000);
        if(ret > 0)
        {

            if(0x25==tmp[2]&&0x02==tmp[0])
            {
                m_msg.append(0x2A);
            }else if(0x27==tmp[2])
            {
                m_msg.append(0x30);
            }else if(0x28==tmp[2])
            {
                emit message(m_msg);
                m_msg.clear();
            }else if(0x1D<tmp[2]&&0x27>tmp[2]){
                m_msg.append(tmp[2]+0x13);
            }else if(0x03<tmp[2]&&0x1E>tmp[2]){
                if(0x02==tmp[0]){
                    m_msg.append(tmp[2]+0x3D);
                }else{
                    m_msg.append(tmp[2]+0x5D);
                }

            }

        }

        QMutexLocker locker(&m_lock);
        if(!m_isCanRun)
        {
            return;
        }
    }
}

void UsbMonitor::stopImmediately()
{
    qDebug() << "SubThread closed";
    QMutexLocker locker(&m_lock);
    m_isCanRun = false;
}
