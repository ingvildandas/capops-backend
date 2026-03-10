#include "HttpServer.hpp"

#include <QDebug>
#include <QHostAddress>

#include "../Network/HttpRouter.hpp"
#include "../Controllers/RiskEventController.hpp"

HttpServer::HttpServer(quint16 port, QObject* parent)
    : QObject(parent),
      _port(port)
{
}

bool HttpServer::start()
{
    if (!_tcpServer.listen(QHostAddress::Any, _port))
    {
        qCritical() << "HTTP server failed to start";
        return false;
    }

    _httpServer.bind(&_tcpServer);

    qDebug() << "HTTP server listening on port" << _port;

    return true;
}


void HttpRouter::registerRiskEventController
(
    RiskEventController& riskEventController
)
{}