#include <QString>

#include "Models/RiskEvent.hpp"

RiskEvent::RiskEvent()
    :
    _riskEventId(0), 
    _sectorId(0),
    _acknowledged(false),
    _riskSeverity(""),
    _createdTimestamp(QDateTime::currentDateTimeUtc()),
    _acknowledgedTimestamp(QDateTime()),
    _message("")
{}

RiskEvent::RiskEvent
(
    const int riskEventId,
    const int sectorId,
    const bool acknowledged,
    const QString& riskSeverity,
    const QDateTime& createdTimestamp,
    const QDateTime& acknowledgedTimestamp,
    const QString& message
)
    : 
    _riskEventId(riskEventId), 
    _sectorId(sectorId),
    _acknowledged(acknowledged),
    _riskSeverity(riskSeverity),
    _createdTimestamp(createdTimestamp),
    _acknowledgedTimestamp(acknowledgedTimestamp),
    _message(message)
{}

const int RiskEvent::getRiskEventId() const 
{
    return _riskEventId;
}

const int RiskEvent::getSectorId() const
{
    return _sectorId;
}

const bool RiskEvent::getAcknowledged() const
{
    return _acknowledged;
}

const QString& RiskEvent::getRiskSeverity() const
{
    return _riskSeverity;
}

const QDateTime& RiskEvent::getCreatedTimestamp() const
{
    return _createdTimestamp;
}

const QDateTime& RiskEvent::getAcknowledgedTimestamp() const
{
    return _acknowledgedTimestamp;
}

const QString& RiskEvent::getMessage() const
{
    return _message;
}