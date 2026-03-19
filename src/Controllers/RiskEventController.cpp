#include <vector>

#include <QHttpServerResponse>
#include <QHttpServerResponder>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QDateTime>
#include <QWebSocket>

#include "Controllers/RiskEventController.hpp"
#include "Converters/RiskEventConverter.hpp"
#include "Exceptions/DatabaseException.hpp"
#include "Models/RiskEvent.hpp"
#include "Services/RiskEventService.hpp"

RiskEventController::RiskEventController
(
    RiskEventService& service,
    FlightDataStateManager& stateManager,
    QObject* parent
)
    : 
    _service(service), 
    _stateManager(stateManager), 
    QObject(parent)
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
    catch (const DatabaseException&)
    {
        return QHttpServerResponse(QHttpServerResponder::StatusCode::NotFound);
    }
    catch (const std::exception& e)
    {
        qWarning() << "Unexpected error occurred: " << e.what();
        return QHttpServerResponse(QHttpServerResponder::StatusCode::InternalServerError);
    }
    catch(...)
    {
        qWarning() << "Unknown error occurred";
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
        std::vector<RiskEvent> riskEvents = _service.getMultipleRiskEvents
        (
            count, 
            acknowledged, 
            fromTimestamp, 
            toTimestamp
        );
        QJsonArray jsonArray = RiskEventConverter::toJson(riskEvents);

        return QHttpServerResponse
        (
            "application/json", 
            QJsonDocument(jsonArray).toJson()
        );
    }
    catch (const DatabaseException& e)
    {
        qWarning() << e.what();
        return QHttpServerResponse(QHttpServerResponder::StatusCode::InternalServerError);
    }
    catch(std::exception& e)
    {
        qWarning() << "Unexpected error occurred: " << e.what();
        return QHttpServerResponse(QHttpServerResponder::StatusCode::InternalServerError);
    }
    catch(...)
    {
        qWarning() << "Unknown error occurred";
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
            riskEvent.getAcknowledged(),
            _stateManager
        );
        return QHttpServerResponse(QHttpServerResponder::StatusCode::NoContent);
    }
    catch (const DatabaseException&)
    {
        return QHttpServerResponse(QHttpServerResponder::StatusCode::NotFound);
    }
    catch (const std::exception& e)
    {
        qWarning() << "Unexpected error occurred: " << e.what();
        return QHttpServerResponse(QHttpServerResponder::StatusCode::InternalServerError);
    }
    catch (...)
    {
        qWarning() << "Unknown error occurred";
        return QHttpServerResponse(QHttpServerResponder::StatusCode::InternalServerError);
    }
}

QHttpServerResponse RiskEventController::deleteRiskEvent
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
        _service.deleteRiskEvent(riskEventId);
        return QHttpServerResponse(QHttpServerResponder::StatusCode::NoContent);
    }
    catch (const DatabaseException& e)
    {
        return QHttpServerResponse(QHttpServerResponder::StatusCode::NotFound);
    }
    catch (const std::exception& e)
    {
        qWarning() << "Unexpected error occurred: " << e.what();
        return QHttpServerResponse(QHttpServerResponder::StatusCode::InternalServerError);
    }
    catch (...)
    {
        qWarning() << "Unknown error occurred";
        return QHttpServerResponse(QHttpServerResponder::StatusCode::InternalServerError);
    }
}