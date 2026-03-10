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
    _httpServer.route("/risk-event/id/<arg>", QHttpServerRequest::Method::Get,
        [&riskEventController](const int riskEventId, const QHttpServerRequest& request) {
            return riskEventController.getRiskEvent(riskEventId, request);
        });
        
    _httpServer.route("/risk-event", QHttpServerRequest::Method::Get,
        [&riskEventController](const QHttpServerRequest& request) {

            int* count = nullptr;
            bool* acknowledged = nullptr;
            QString* from = nullptr;
            QString* to = nullptr;

            HttpServer::handleQueryParams(request, count, acknowledged, from, to);
            return riskEventController.getMultipleRiskEvents
            (
                request, 
                *count, 
                *acknowledged,
                *from,
                *to
            );
        });
        
    _httpServer.route("/risk-event/id/<arg>", QHttpServerRequest::Method::Put,
        [&riskEventController](int riskEventId, const QHttpServerRequest& request) {
            return riskEventController.updateRiskEvent(riskEventId, request);
        });
        
    _httpServer.route("/risk-event/id/<arg>", QHttpServerRequest::Method::Delete,
        [&riskEventController](int riskEventId, const QHttpServerRequest& request) {
            return riskEventController.deleteRiskEvent(riskEventId, request);
        });
}

void HttpServer::handleQueryParams
(
    const QHttpServerRequest& request,
    int* count, 
    bool* acknowledged,
    QString* from,
    QString* to
)
{
    *count = RiskEventController::DEFAULT_COUNT;
    *acknowledged = RiskEventController::DEFAULT_ACKNOWLEDGED;
    *from = RiskEventController::DEFAULT_FROM;
    *to = RiskEventController::DEFAULT_TO;

    auto query = request.query();
    if (query.hasQueryItem("count"))
    {
        *count = query.queryItemValue("count").toInt();
    }
    if (query.hasQueryItem("acknowledged"))
    {
        *acknowledged = QVariant(query.queryItemValue("acknowledged")).toBool();
    }
    if (query.hasQueryItem("from"))
    {
        *from = query.queryItemValue("from");
    }
    if (query.hasQueryItem("to"))
    {
        *to = query.queryItemValue("to");
    }
}