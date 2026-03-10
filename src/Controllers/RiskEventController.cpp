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

QHttpServerResponse RiskEventController::getMultipleRiskEvents
(
        const QHttpServerRequest& request,
        const int count,
        const bool acknowledged,
        const QString& from,
        const QString& to
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