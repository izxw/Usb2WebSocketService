#include <QCoreApplication>
#include <QDebug>
#include "dlog.h"
#include "winservice.h"

int main(int argc, char *argv[])
{
#ifdef QT_NO_DEBUG
#define Debug(str)(qDebug()<<str)
#else
#define Debug(str)
    qInstallMessageHandler(myMsgOutput);
#endif
    WinService service(argc, argv);
    return service.exec();

}
