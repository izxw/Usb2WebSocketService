#include "winservice.h"

WinService::WinService(int argc, char* argv[])
    :QtService<QCoreApplication>(argc, argv, "MyService")
{
}
void WinService::start()
{
    m_server = new WebService(true);
//    QObject::connect(m_server, &WebService::closed, this, &WinService::exit);
}

void WinService::stop()
{

}

void WinService::pause()
{
}

void WinService::resume()
{
}

