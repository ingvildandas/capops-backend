#pragma once

#include <QObject>
#include <QHttpServer>
#include <QTcpServer>

class RiskEventController;
class QHttpServerRequest;

class HttpServer : public QObject
{
    Q_OBJECT

public:
    explicit HttpServer(quint16 port, QObject* parent = nullptr);

    quint16 getPort() const;
    
    void start();
    void registerRiskEventController(RiskEventController& riskEventController);

private:
    quint16 _port;
    QHttpServer _httpServer;
    QTcpServer _tcpServer;

private:
    struct RiskEventQuery
    {
        int count;
        bool acknowledged;
        QString from;
        QString to;
    };

private:
    static RiskEventQuery parseRiskEventQuery(const QHttpServerRequest& request);
};