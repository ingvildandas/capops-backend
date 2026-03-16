
#include <string>
#include <vector>

#include <QString>

#include "Models/MergedRiskEvent.hpp"
#include "Models/RiskEvent.hpp"
#include "Exceptions/EntityModelException.hpp"

MergedRiskEvent::MergedRiskEvent
(
    const int sectorId,
    const std::vector<RiskEvent>& riskEvents
)
    : _sectorId(sectorId), _riskEvents(riskEvents)
{
    updateSummaryInfo();
}

int MergedRiskEvent::getSectorId() const
{
    return _sectorId;
}

std::vector<RiskEvent> MergedRiskEvent::getRiskEvents() const
{
    return _riskEvents;
}

QString MergedRiskEvent::getSummaryMessage() const
{
    return _summaryMessage;
}

QString MergedRiskEvent::getLastMessage() const
{
    return _lastMessage;
}

void MergedRiskEvent::setRiskEvents(const std::vector<RiskEvent>& riskEvents)
{
    _riskEvents = riskEvents;
    updateSummaryInfo();
}

void MergedRiskEvent::addRiskEvents(const std::vector<RiskEvent>& riskEvents)
{
    for (RiskEvent riskEvent : riskEvents)
    {
        addRiskEvent(riskEvent);
    }

    updateSummaryInfo();
}

void MergedRiskEvent::addRiskEvent(const RiskEvent& riskEvent)
{
    _riskEvents.push_back(riskEvent);
}

void MergedRiskEvent::setSummaryInfo
(
    RiskEvent* lastRiskEvent,
    RiskEvent* secondLastRiskEvent
)
{

    if (!lastRiskEvent && !secondLastRiskEvent)
    {
        _currentSeverity = "";
        _previousSeverity = "";
        _summaryMessage = 
            "Risk severity in sector " + 
            QString::number(_sectorId) + 
            " unknown";
    }
    else if (lastRiskEvent != nullptr && !secondLastRiskEvent)
    {
        _currentSeverity = lastRiskEvent->getRiskSeverity();
        _lastMessage = lastRiskEvent->getMessage();
        _summaryMessage = "Risk severity in sector " + 
            QString::number(_sectorId) + 
            " changed to " +
            _currentSeverity;
    }
    else if (lastRiskEvent != nullptr && secondLastRiskEvent != nullptr)
    {
        _previousSeverity = secondLastRiskEvent->getRiskSeverity();
        _summaryMessage = 
            "Risk severity in sector " + 
            QString::number(_sectorId) + 
            " changed from " +
            _previousSeverity +
            " to " +
            _currentSeverity;
    }
    else 
    {
        _currentSeverity = "";
        _previousSeverity = "";
        throw EntityModelException
        (
            "Unexpected bahavior while determining last and " \
            "second-last risk event for MergedRiskEvent"
        );
    }
}

void MergedRiskEvent::updateSummaryInfo()
{
    RiskEvent* lastRiskEvent = nullptr;
    RiskEvent* secondLastRiskEvent = nullptr;
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
            secondLastRiskEvent = lastRiskEvent;
            lastRiskEvent = &riskEvent;
        }
    }
}