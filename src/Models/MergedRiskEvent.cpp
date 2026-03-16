
#include <vector>

#include <QString>

#include "Models/RiskEventMerged.hpp"
#include "Models/RiskEvent.hpp"

RiskEventMerged::RiskEventMerged
(
    const int sectorId,
    const std::vector<RiskEvent>& riskEvents
)
    : _sectorId(sectorId), _riskEvents(riskEvents)
{
    setSummaryMessage();
}

int RiskEventMerged::getSectorId() const
{
    return _sectorId;
}

std::vector<RiskEvent> RiskEventMerged::getRiskEvents() const
{
    return _riskEvents;
}

void RiskEventMerged::setRiskEvents(const std::vector<RiskEvent>& riskEvents)
{
    _riskEvents = riskEvents;
    setLastMessage();
}

void RiskEventMerged::addRiskEvents(const std::vector<RiskEvent>& riskEvents)
{
    for (RiskEvent riskEvent : riskEvents)
    {
        addRiskEvent(riskEvent);
    }

    setLastMessage();
}

void RiskEventMerged::addRiskEvent(const RiskEvent& riskEvent)
{
    _riskEvents.push_back(riskEvent);
}

void RiskEventMerged::setSummaryMessage()
{
    _summaryMessage = "Risk events for sector " + _sectorId;
}

void RiskEventMerged::setLastMessage()
{
    RiskEvent* lastRiskEvent = nullptr;
    for (RiskEvent riskEvent : _riskEvents)
    {
        if (!lastRiskEvent)
        {
            lastRiskEvent = &riskEvent;
            continue;
        }

        if 
        (
            riskEvent.getCreatedTimestamp() > 
            lastRiskEvent->getCreatedTimestamp()
        )
        {
            lastRiskEvent = &riskEvent;
        }
    }

    if (!lastRiskEvent) _summaryMessage = "";
    else _lastMessage = lastRiskEvent->getMessage();
}