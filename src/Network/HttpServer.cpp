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

            RiskEventQuery params = HttpServer::parseRiskEventQuery(request);

            return riskEventController.getMultipleRiskEvents
            (
                request, 
                params.count, 
                params.acknowledged,
                params.from,
                params.to
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

HttpServer::RiskEventQuery HttpServer::parseRiskEventQuery(const QHttpServerRequest& request)
{
    RiskEventQuery params {
        RiskEventController::DEFAULT_COUNT,
        RiskEventController::DEFAULT_ACKNOWLEDGED,
        RiskEventController::DEFAULT_FROM,
        RiskEventController::DEFAULT_TO
    };

    auto query = request.query();
    if (query.hasQueryItem("count"))
    {
        params.count = query.queryItemValue("count").toInt();
    }
    if (query.hasQueryItem("acknowledged"))
    {
        params.acknowledged = QVariant(query.queryItemValue("acknowledged")).toBool();
    }
    if (query.hasQueryItem("from"))
    {
        params.from = query.queryItemValue("from");
    }
    if (query.hasQueryItem("to"))
    {
        params.to = query.queryItemValue("to");
    }

    return params;
}