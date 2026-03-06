#include <QHttpServerResponse>
#include <QHttpServerResponder>
#include <QObject>
#include <QWebSocket>

#include "Controllers/RiskEventController.hpp"

RiskEventController::RiskEventController
(
    RiskEventService& service,
    QObject* parent
)
    : _service(service), QObject(parent)
{}

QHttpServerResponse RiskEventController::getRiskEvent
(
    const int id, 
    const QHttpServerRequest& request
)
{
    return QHttpServerResponder::StatusCode::NotImplemented;
}

QHttpServerResponse RiskEventController::getMostRecentRiskEvents
(
    const QHttpServerRequest& request
)
{
    return QHttpServerResponder::StatusCode::NotImplemented;
}

QHttpServerResponse RiskEventController::getRiskEventsBetween
(
    const QHttpServerRequest& request
)
{
    return QHttpServerResponder::StatusCode::NotImplemented;
}

QHttpServerResponse RiskEventController::updateRiskEvent
(
    const int id, 
    const QHttpServerRequest& request
)
{
    return QHttpServerResponder::StatusCode::NotImplemented;
}

QHttpServerResponse RiskEventController::deleteRiskEvent
(
    const int id, 
    const QHttpServerRequest& request
)
{
    return QHttpServerResponder::StatusCode::NotImplemented;
}