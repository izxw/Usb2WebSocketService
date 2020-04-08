#include "webservice.h"

#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>

QT_USE_NAMESPACE

WebService::WebService(bool debug, QObject *parent)
    : QObject(parent),
      m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
                                              QWebSocketServer::NonSecureMode, this)),
      m_debug(debug)
{
    rx.setPattern("^(config)(1{1}|2{1}|3{1})$");

    quint16 port = 9009;
    serial_1 = "COM1";
    serial_2 = "COM2";
    serial_3 = "COM3";
    num_1 = 1;
    num_2 = 2;
    num_3 = 3;

    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        if (m_debug)
            qDebug() << "Echoserver listening on port LOL" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &WebService::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &WebService::closed);
    }

    //COM1
    m_serialPort_1 = new QSerialPort();
    if(m_serialPort_1->isOpen())
    {
        m_serialPort_1->clear();
        m_serialPort_1->close();
    }
    m_serialPort_1->setPortName(serial_1);
    if(!m_serialPort_1->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
    {
        if (m_debug)
            qDebug()<<"COM"<<"打开失败!";
        return;
    }

    m_serialPort_1->setBaudRate(QSerialPort::Baud9600,QSerialPort::AllDirections);//设置波特率和读写方向
    m_serialPort_1->setDataBits(QSerialPort::Data8);		//数据位为8位
    m_serialPort_1->setFlowControl(QSerialPort::NoFlowControl);//无流控制
    m_serialPort_1->setParity(QSerialPort::NoParity);	//无校验位
    m_serialPort_1->setStopBits(QSerialPort::OneStop); //一位停止位
    //COM2
    m_serialPort_2 = new QSerialPort();
    if(m_serialPort_2->isOpen())
    {
        m_serialPort_2->clear();
        m_serialPort_2->close();
    }
    m_serialPort_2->setPortName(serial_2);
    if(!m_serialPort_2->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
    {
        if (m_debug)
            qDebug()<<"COM"<<"打开失败!";
        return;
    }

    m_serialPort_2->setBaudRate(QSerialPort::Baud9600,QSerialPort::AllDirections);//设置波特率和读写方向
    m_serialPort_2->setDataBits(QSerialPort::Data8);		//数据位为8位
    m_serialPort_2->setFlowControl(QSerialPort::NoFlowControl);//无流控制
    m_serialPort_2->setParity(QSerialPort::NoParity);	//无校验位
    m_serialPort_2->setStopBits(QSerialPort::OneStop); //一位停止位
    //COM3
    m_serialPort_3 = new QSerialPort();
    if(m_serialPort_3->isOpen())
    {
        m_serialPort_3->clear();
        m_serialPort_3->close();
    }
    m_serialPort_3->setPortName(serial_3);
    if(!m_serialPort_3->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
    {
        if (m_debug)
            qDebug()<<"COM"<<"打开失败!";
        return;
    }

    m_serialPort_3->setBaudRate(QSerialPort::Baud9600,QSerialPort::AllDirections);//设置波特率和读写方向
    m_serialPort_3->setDataBits(QSerialPort::Data8);		//数据位为8位
    m_serialPort_3->setFlowControl(QSerialPort::NoFlowControl);//无流控制
    m_serialPort_3->setParity(QSerialPort::NoParity);	//无校验位
    m_serialPort_3->setStopBits(QSerialPort::OneStop); //一位停止位

    connect(m_serialPort_1,&QSerialPort::readyRead,this,[=](){reciveCom2Ws_1(num_1);});
    connect(m_serialPort_2,&QSerialPort::readyRead,this,[=](){reciveCom2Ws_2(num_2);});
    connect(m_serialPort_3,&QSerialPort::readyRead,this,[=](){reciveCom2Ws_3(num_3);});

}


WebService::~WebService()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void WebService::onNewConnection()
{
    qDebug() << "new connection!";
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();
    if (!pSocket)
        return;

    connect(pSocket, &QWebSocket::textMessageReceived, this, &WebService::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WebService::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &WebService::socketDisconnected);

    // load all previous messages
    foreach (auto k, log) {
        pSocket->sendTextMessage(k);
    }
    m_clients << pSocket;
}

void WebService::processTextMessage(QString message)
{
    foreach (auto k, m_clients)
    {
        QWebSocket *pClient = qobject_cast<QWebSocket *>(k);
        if (pClient)
        {
            log.push_back(message);
            pClient->sendTextMessage(message);
        }
    }
}

void WebService::reciveCom2Ws_1(int num)
{
    QByteArray info;
    switch (num) {
    case 1:{
        info = m_serialPort_1->readAll();
        if (rx.indexIn(info) > -1) {
            num_1 = rx.cap(2).toUShort();
        }
        foreach (auto k, m_clients)
        {
            QWebSocket *pClient = qobject_cast<QWebSocket *>(k);
            if (pClient)
            {
                pClient->sendTextMessage("c1:"+info);
            }
        }
        break;
    }
    case 2:
        info = m_serialPort_1->readAll();
        if (rx.indexIn(info) > -1) {
            num_1 = rx.cap(2).toUShort();
        }
        foreach (auto k, m_clients)
        {
            QWebSocket *pClient = qobject_cast<QWebSocket *>(k);
            if (pClient)
            {
                pClient->sendTextMessage("c2:"+info);
            }
        }
        break;
    case 3:
        info = m_serialPort_1->readAll();
        if (rx.indexIn(info) > -1) {
            num_1 = rx.cap(2).toUShort();
        }
        foreach (auto k, m_clients)
        {
            QWebSocket *pClient = qobject_cast<QWebSocket *>(k);
            if (pClient)
            {
                pClient->sendTextMessage("c3:"+info);
            }
        }
        break;
    }
}

void WebService::reciveCom2Ws_2(int num)
{
    QByteArray info;
    switch (num) {
    case 1:
        info = m_serialPort_2->readAll();
        if (rx.indexIn(info) > -1) {
            num_2 = rx.cap(2).toUShort();
        }
        foreach (auto k, m_clients)
        {
            QWebSocket *pClient = qobject_cast<QWebSocket *>(k);
            if (pClient)
            {
                pClient->sendTextMessage("c1:"+info);
            }
        }
        break;
    case 2:
        info = m_serialPort_2->readAll();
        if (rx.indexIn(info) > -1) {
            num_2 = rx.cap(2).toUShort();
        }
        foreach (auto k, m_clients)
        {
            QWebSocket *pClient = qobject_cast<QWebSocket *>(k);
            if (pClient)
            {
                pClient->sendTextMessage("c2:"+info);
            }
        }
        break;
    case 3:
        info = m_serialPort_2->readAll();
        if (rx.indexIn(info) > -1) {
            num_2 = rx.cap(2).toUShort();
        }
        foreach (auto k, m_clients)
        {
            QWebSocket *pClient = qobject_cast<QWebSocket *>(k);
            if (pClient)
            {
                pClient->sendTextMessage("c3:"+info);
            }
        }
        break;
    }
}

void WebService::reciveCom2Ws_3(int num)
{
    QByteArray info;
    switch (num) {
    case 1:
        info = m_serialPort_3->readAll();
        if (rx.indexIn(info) > -1) {
            num_3 = rx.cap(2).toUShort();
        }
        foreach (auto k, m_clients)
        {
            QWebSocket *pClient = qobject_cast<QWebSocket *>(k);
            if (pClient)
            {
                pClient->sendTextMessage("c1:"+info);
            }
        }
        break;
    case 2:
        info = m_serialPort_3->readAll();
        if (rx.indexIn(info) > -1) {
            num_3 = rx.cap(2).toUShort();
        }
        foreach (auto k, m_clients)
        {
            QWebSocket *pClient = qobject_cast<QWebSocket *>(k);
            if (pClient)
            {
                pClient->sendTextMessage("c2:"+info);
            }
        }
        break;
    case 3:
        info = m_serialPort_3->readAll();
        if (rx.indexIn(info) > -1) {
            num_3 = rx.cap(2).toUShort();
        }
        foreach (auto k, m_clients)
        {
            QWebSocket *pClient = qobject_cast<QWebSocket *>(k);
            if (pClient)
            {
                pClient->sendTextMessage("c3:"+info);
            }
        }
        break;
    }

}

void WebService::processBinaryMessage(QByteArray message)
{
    qDebug() << "new Binary Message";

    QJsonObject json = QJsonDocument::fromJson(message).object();
    qDebug() << json;
    if (json.contains(QStringLiteral("textMessage")))
        textMessage(sender(), json);
    else if (json.contains(QStringLiteral("loginIn")))
        loginIn(sender(), json);
    else if (json.contains(QStringLiteral("getCurrentUsers")))
        getCurrentUsers(sender(), json);
    else if (json.contains(QStringLiteral("getHistory")))
        getHistory(sender(), json);
    else if (json.contains(QStringLiteral("newRegistration")))
        newRegistration(sender(), json);
}

void WebService::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        currentUsers.remove(pClient);
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

void WebService::textMessage(QObject *sender, const QJsonObject &json)
{
    QString name = json[QStringLiteral("textMessage")].toArray().at(0).toString();
    QString msg = json[QStringLiteral("textMessage")].toArray().at(1).toString();
    QString finalMessage = name + ": " + msg;

    log.push_back(finalMessage);
    foreach (auto k, m_clients)
    {
        QWebSocket *pClient = qobject_cast<QWebSocket *>(k);
        if (pClient)
            pClient->sendTextMessage(finalMessage);
    }
}

void WebService::loginIn(QObject *sender, const QJsonObject &json)
{
    QString login = json[QStringLiteral("loginIn")].toArray().at(0).toString();
    QString password = json[QStringLiteral("loginIn")].toArray().at(1).toString();
    QWebSocket *p = qobject_cast<QWebSocket *>(sender);
    if (p)
        currentUsers[p] = login;
}

void WebService::getCurrentUsers(QObject *sender, const QJsonObject &json)
{
    QString name = json[QStringLiteral("getCurrentUsers")].toArray().at(0).toString();
    // we don't need name right now, but let it be
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender);
    if (pClient)
    {
        QJsonObject json;
        QJsonArray array;
        foreach (auto k, currentUsers) {
            array << k;
        }
        json[QStringLiteral("currentUsers")] = array;
        QJsonDocument doc(json);
        qDebug() << json;
        pClient->sendBinaryMessage(doc.toJson());
    }
}

void WebService::getHistory(QObject *sender, const QJsonObject &json)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender);
    if (pClient)
    {
        QJsonObject json;
        QJsonArray array;
        foreach (auto k, log) {
            array << k;
        }
        json[QStringLiteral("history")] = array;
        QJsonDocument doc(json);
        qDebug() << json;
        pClient->sendBinaryMessage(doc.toJson());
    }
}

void WebService::newRegistration(QObject *sender, const QJsonObject &json)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender);
    if (pClient)
    {
        QJsonObject json;
        QJsonArray array;
        if (true) // if account OK
            array <<
                     json[QStringLiteral("registration")] = array;
    }
}
