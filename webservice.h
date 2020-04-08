#ifndef WEBSERVICE_H
#define WEBSERVICE_H

#include <QObject>
#include <QList>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMap>
#include <QtSerialPort/QSerialPort>
#include <QSettings>
#include <QDebug>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class WebService : public QObject
{
    Q_OBJECT
public:
    explicit WebService(bool debug = false, QObject *parent = Q_NULLPTR);
    ~WebService();
Q_SIGNALS:
    void closed();
private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();
    void textMessage(QObject *sender, const QJsonObject &json);
    void loginIn(QObject *sender, const QJsonObject &json);
    void getCurrentUsers(QObject *sender, const QJsonObject &json);
    void getHistory(QObject *sender, const QJsonObject &json);
    void newRegistration(QObject *sender, const QJsonObject &json);
    void reciveCom2Ws_1(int num);
    void reciveCom2Ws_2(int num);
    void reciveCom2Ws_3(int num);

private:
    QWebSocketServer *m_pWebSocketServer;
    bool m_debug;
    QSettings* setting;

    QList<QWebSocket *> m_clients;
    QList<QString> log;
    QMap<QWebSocket *, QString> currentUsers;
    QSerialPort *m_serialPort_1;
    QSerialPort *m_serialPort_2;
    QSerialPort *m_serialPort_3;

    QString serial_1;
    QString serial_2;
    QString serial_3;
    quint16 num_1;
    quint16 num_2;
    quint16 num_3;

    QRegExp rx;

};

#endif // WEBSERVICE_H
