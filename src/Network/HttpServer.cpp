#include <QDebug>
#include <QHostAddress>

#include "Network/HttpServer.hpp"
#include "Controllers/RiskEventController.hpp"

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


void HttpServer::registerRiskEventController
(
    RiskEventController& riskEventController
)
{
    _httpServer.route("/albums/<arg>", QHttpServerRequest::Method::Get,
        [&riskEventController](int riskEventId, const QHttpServerRequest& request) {
            return riskEventController.getRiskEvent(riskEventId, request);
        });
        
    _httpServer.route("/albums", QHttpServerRequest::Method::Get,
        [&riskEventController](const QHttpServerRequest& request) {
            return riskEventController.getMostRecentRiskEvents(request);
        });
        
    _httpServer.route("/albums/<arg>", QHttpServerRequest::Method::Put,
        [&riskEventController](int riskEventId, const QHttpServerRequest& request) {
            return riskEventController.updateRiskEvent(riskEventId, request);
        });
        
    _httpServer.route("/albums/<arg>", QHttpServerRequest::Method::Delete,
        [&riskEventController](int riskEventId, const QHttpServerRequest& request) {
            return riskEventController.deleteRiskEvent(riskEventId, request);
        });
}