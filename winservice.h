#ifndef WINSERVICE_H
#define WINSERVICE_H

#include "qtservice.h"
#include "webservice.h"

class WinService : public QtService<QCoreApplication>
{
public:
    WinService(int argc, char* argv[]);
    ~WinService(){}
public:
    void start();
    void pause();
    void resume();
    void stop();
private:
    WebService *m_server = nullptr;
};

#endif // WINSERVICE_H
