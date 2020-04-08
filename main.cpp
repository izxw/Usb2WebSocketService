#include <QCoreApplication>
#include <QDebug>
#include "dlog.h"
#include "winservice.h"

int main(int argc, char *argv[])
{
#ifdef QT_NO_DEBUG
#define Debug(str)
    qInstallMessageHandler(myMsgOutput);
#else
#define Debug(str)(qDebug()<<str)
#endif
    WinService service(argc, argv);
    return service.exec();
}
