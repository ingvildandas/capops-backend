#include <vector>

#include <QHttpServerResponse>
#include <QHttpServerResponder>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QDateTime>
#include <QWebSocket>

#include "Controllers/RiskEventController.hpp"
#include "ModelConverters/RiskEventConverter.hpp"
#include "Services/RiskEventService.hpp"

RiskEventController::RiskEventController
(
    RiskEventService& service,
    QObject* parent
)
    : _service(service), QObject(parent)
{}

QHttpServerResponse RiskEventController::getRiskEvent
(
    const int riskEventId, 
    const QHttpServerRequest& request
)
{
    if (riskEventId <= 0)
    {
        return QHttpServerResponse(QHttpServerResponder::StatusCode::BadRequest);
    }

    try
    {
        RiskEvent riskEvent = _service.getRiskEvent(riskEventId);
        QJsonObject json = RiskEventConverter::toJson(riskEvent);

        return QHttpServerResponse
        (
            "application/json", 
            QJsonDocument(json).toJson()
        );
    }
    catch (const std::runtime_error&)
    {
        return QHttpServerResponse(QHttpServerResponder::StatusCode::NotFound);
    }
    catch(...)
    {
        return QHttpServerResponse(QHttpServerResponder::StatusCode::InternalServerError);
    }
    
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
    QDateTime fromTimestamp = QDateTime::fromSecsSinceEpoch(0);
    QDateTime toTimestamp = QDateTime::currentDateTimeUtc();

    if (!from.isEmpty() && QDateTime::fromString(from).isValid())
    {
        fromTimestamp = QDateTime::fromString(from);
    }
    
    if (!to.isEmpty() && QDateTime::fromString(to).isValid())
    {
        toTimestamp = QDateTime::fromString(to);
    }

    try
    {
        std::vector<const RiskEvent> riskEvents = _service.getMultipleRiskEvents
        (
            count, 
            acknowledged, 
            fromTimestamp, 
            toTimestamp
        );
        QJsonObject json = RiskEventConverter::toJson(riskEvents);

        return QHttpServerResponse
        (
            "application/json", 
            QJsonDocument(json).toJson()
        );
    }
    catch(...)
    {
        return QHttpServerResponse(QHttpServerResponder::StatusCode::InternalServerError);
    }
}

QHttpServerResponse RiskEventController::updateRiskEvent
(
    const int riskEventId, 
    const QHttpServerRequest& request
)
{
    if (riskEventId <= 0)
    {
        return QHttpServerResponse(QHttpServerResponder::StatusCode::BadRequest);
    }

    const QJsonDocument document = QJsonDocument::fromJson(request.body());
    if (!document.isObject())
    {
        return QHttpServerResponse(QHttpServerResponder::StatusCode::BadRequest);
    }

    try
    {
        RiskEvent riskEvent = RiskEventConverter::fromJson(document.object());
        _service.updateAcknowledged
        (
            riskEvent.getRiskEventId(), 
            riskEvent.getAcknowledged()
        );
        return QHttpServerResponse(QHttpServerResponder::StatusCode::NoContent);
    }
    catch (const std::runtime_error&)
    {
        return QHttpServerResponse(QHttpServerResponder::StatusCode::NotFound);
    }
    catch (...)
    {
        return QHttpServerResponse(QHttpServerResponder::StatusCode::InternalServerError);
    }
}

QHttpServerResponse RiskEventController::deleteRiskEvent
(
    const int id, 
    const QHttpServerRequest& request
)
{
    return QHttpServerResponder::StatusCode::NotImplemented;
}