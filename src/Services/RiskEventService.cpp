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

void RiskEventService::updateAcknowledged
(
    const int riskEventId, 
    const bool acknowledged,
    FlightDataStateManager& stateManager
)
{
    _repository.updateAcknowledged(riskEventId, acknowledged);
    const auto updatedRiskEvent = _repository.selectById(riskEventId);
    const auto currentRiskEventData = stateManager.getState().getRiskEventData();
    const auto updatedRiskEventData = RiskEventData
    (
        currentRiskEventData.getRiskEventCount(), 
        std::vector<RiskEvent>{updatedRiskEvent}
    );
    updateState(updatedRiskEventData, stateManager);
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
    auto newMergedRiskEvents = riskEventData.getMergedRiskEvents();
    auto stateMergedRiskEvents = 
        stateManager.getState().getRiskEventData().getMergedRiskEvents();

    if 
    (
        newMergedRiskEvents.empty() || 
        stateMergedRiskEvents.empty()
    )
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