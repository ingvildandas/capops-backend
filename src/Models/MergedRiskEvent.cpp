
#include <vector>

#include <QString>

#include "Models/MergedRiskEvent.hpp"
#include "Models/RiskEvent.hpp"

MergedRiskEvent::MergedRiskEvent
(
    const int sectorId,
    const std::vector<RiskEvent>& riskEvents
)
    : _sectorId(sectorId), _riskEvents(riskEvents)
{
    setSummaryMessage();
}

int MergedRiskEvent::getSectorId() const
{
    return _sectorId;
}

std::vector<RiskEvent> MergedRiskEvent::getRiskEvents() const
{
    return _riskEvents;
}

void MergedRiskEvent::setRiskEvents(const std::vector<RiskEvent>& riskEvents)
{
    _riskEvents = riskEvents;
    setLastMessage();
}

void MergedRiskEvent::addRiskEvents(const std::vector<RiskEvent>& riskEvents)
{
    for (RiskEvent riskEvent : riskEvents)
    {
        addRiskEvent(riskEvent);
    }

    setLastMessage();
}

void MergedRiskEvent::addRiskEvent(const RiskEvent& riskEvent)
{
    _riskEvents.push_back(riskEvent);
}

void MergedRiskEvent::setSummaryMessage()
{
    _summaryMessage = "Risk events for sector " + _sectorId;
}

void MergedRiskEvent::setLastMessage()
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