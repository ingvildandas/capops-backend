#include <QString>

#include "Models/RiskEvent.hpp"

RiskEvent::RiskEvent
(
    const int riskEventId,
    const int riskSeverity,
    const QString& message,
    const bool acknowledged
)
    : 
    _riskEventId(riskEventId), 
    _riskSeverity(riskSeverity),
    _message(message),
    _acknowledged(acknowledged)
{}

const int RiskEvent::getRiskEventId() const 
{
    return _riskEventId;
}

const int RiskEvent::getRiskSeverity() const
{
    return _riskSeverity;
}

const QString& RiskEvent::getMessage() const
{
    return _message;
}

const bool RiskEvent::getAcknowledged() const
{
    return _acknowledged;
}