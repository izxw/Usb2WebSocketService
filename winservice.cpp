#include "winservice.h"

WinService::WinService(int argc, char* argv[])
    :QtService<QCoreApplication>(argc, argv, "NxPostUsbMonitor")
{
    setStartupType(QtServiceController::StartupType::AutoStartup);
}
void WinService::start()
{
    m_server = new WebService(false);
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

