#include <unordered_set>
#include <vector>

#include <QDateTime>

#include "Services/RiskEventService.hpp"
#include "Managers/FlightDataStateManager.hpp"
#include "Models/FlightData.hpp"
#include "Models/RiskEvent.hpp"
#include "Models/RiskEventData.hpp"
#include "Repositories/IRiskEventRepository.hpp"
#include "Structs/FlightDataStructs.hpp"

RiskEventService::RiskEventService(IRiskEventRepository& repository)
    : _repository(repository)
{}

RiskEvent RiskEventService::getRiskEvent(const int riskEventId)
{
    return _repository.selectById(riskEventId);
}

std::vector<RiskEvent> RiskEventService::getMultipleRiskEvents(const int count)
{
    return _repository.selectMultipleByCount(count);
}

std::vector<RiskEvent> RiskEventService::getMultipleRiskEvents
(
    const int count, 
    const bool acknowledged
)
{
    return _repository.selectMultipleByAcknowledged(count, acknowledged);
}

std::vector<RiskEvent> RiskEventService::getMultipleRiskEvents
(
    const int count,
    const QDateTime& from,
    const QDateTime& to
)
{
    return _repository.selectMultipleByTimestamps(count, from, to);
}

std::vector<RiskEvent> RiskEventService::getMultipleRiskEvents
(
    const int count,
    const bool acknowledged,
    const QDateTime& from,
    const QDateTime& to
)
{
    return _repository.selectMultipleByParameters
    (
        count, 
        acknowledged, 
        from, 
        to
    );
}

void RiskEventService::registerRiskEvent(const RiskEvent& riskEvent)
{
    _repository.insert(riskEvent);
}

void RiskEventService::registerMultipleRiskEvents
(
    const std::vector<RiskEvent>& riskEvents
)
{
    _repository.insertMultiple(riskEvents);
}

void RiskEventService::acknowledgeRiskEvents
(
    const std::vector<int>& riskEventIds,
    FlightDataStateManager& stateManager
)
{
    _repository.updateMultipleAcknowledged(riskEventIds);

    const auto currentRiskEventData = stateManager.getState().getRiskEventData();

    std::vector<RiskEvent> currentRiskEvents = currentRiskEventData.getRiskEvents();
    
    std::vector<RiskEvent> updatedRiskEvents;
    updatedRiskEvents.reserve(currentRiskEvents.size());

    std::unordered_set<int> idsToAck
    (
        riskEventIds.begin(),
        riskEventIds.end()
    );

    for (const auto& riskEvent : currentRiskEvents)
    {
        if (idsToAck.find(riskEvent.getRiskEventId()) == idsToAck.end())
        {
            updatedRiskEvents.push_back(riskEvent);
        }
    }

    RiskEventData updatedRiskEventData
    (
        static_cast<int>(updatedRiskEvents.size()), 
        updatedRiskEvents
    );

    stateManager.setRiskEventData(updatedRiskEventData);
}

void RiskEventService::deleteRiskEvent(const int riskEventId)
{
    _repository.deleteById(riskEventId);
}

void RiskEventService::updateState
(
    const RiskEventData& riskEventData, 
    FlightDataStateManager& stateManager
)
{
    if (!stateManager.hasRiskEventData())
    {
        stateManager.setRiskEventData(riskEventData);
        return;
    }

    auto newMergedRiskEvents = riskEventData.getMergedRiskEvents();
    auto stateMergedRiskEvents = 
        stateManager.getState().getRiskEventData().getMergedRiskEvents();

    if (stateMergedRiskEvents.empty())
    {
        stateManager.setRiskEventData(riskEventData);
        return;
    }
    
    auto newRiskEvents = riskEventData.getRiskEvents();
    auto stateRiskEvents = 
        stateManager.getState().getRiskEventData().getRiskEvents();

    stateRiskEvents.reserve
    (
        stateRiskEvents.size() + newRiskEvents.size()
    );
    stateRiskEvents.insert
    (
        stateRiskEvents.end(), 
        newRiskEvents.begin(), 
        newRiskEvents.end()
    );
    int updatedRiskEventCount = static_cast<int>(stateRiskEvents.size());
    RiskEventData updatedRiskEventData
    (
        updatedRiskEventCount, 
        stateRiskEvents
    );

    stateManager.setRiskEventData(updatedRiskEventData);
}