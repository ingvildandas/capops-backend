
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
    calculateChecksum();
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

QString MergedRiskEvent::getChecksum() const
{
    return _checksum;
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

void MergedRiskEvent::calculateChecksum()
{
    int numRiskEvents = _riskEvents.size();
    _checksum = QString::number(_sectorId) + QString("/") + QString::number(numRiskEvents);
}

void MergedRiskEvent::setSummaryInfo
(
    const RiskEvent* lastRiskEvent,
    const RiskEvent* secondLastRiskEvent
)
{

    if (!lastRiskEvent && !secondLastRiskEvent)
    {
        _currentSeverity = "";
        _previousSeverity = "";
        _lastMessage = "";
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
        _currentSeverity = lastRiskEvent->getRiskSeverity();
        _previousSeverity = secondLastRiskEvent->getRiskSeverity();
        _lastMessage = lastRiskEvent->getMessage();
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
        _lastMessage = "";
        _summaryMessage = 
            "Risk severity in sector " + 
            QString::number(_sectorId) + 
            " unknown";
        throw EntityModelException
        (
            "Unexpected behavior while determining last and " \
            "second-last risk event for MergedRiskEvent"
        );
    }
}

void MergedRiskEvent::updateSummaryInfo()
{
    RiskEvent* lastRiskEvent = nullptr;
    RiskEvent* secondLastRiskEvent = nullptr;
    for (RiskEvent& riskEvent : _riskEvents)
    {
        if (!lastRiskEvent ||
            riskEvent.getCreatedTimestamp() > lastRiskEvent->getCreatedTimestamp())
        {
            secondLastRiskEvent = lastRiskEvent;
            lastRiskEvent = &riskEvent;
        }
        else if (!secondLastRiskEvent ||
                riskEvent.getCreatedTimestamp() > secondLastRiskEvent->getCreatedTimestamp())
        {
            secondLastRiskEvent = &riskEvent;
        }
    }

    setSummaryInfo(lastRiskEvent, secondLastRiskEvent);
}