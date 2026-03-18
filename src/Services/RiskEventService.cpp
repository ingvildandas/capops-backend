#include <vector>

#include <QDateTime>

#include "Services/RiskEventService.hpp"
#include "Managers/FlightDataStateManager.hpp"
#include "Models/RiskEvent.hpp"
#include "Models/RiskEventData.hpp"
#include "Repositories/IRiskEventRepository.hpp"

RiskEventService::RiskEventService(
    IRiskEventRepository& repository, 
    FlightDataStateManager& stateManager
)
    : _repository(repository), _stateManager(stateManager)
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
    const bool acknowledged
)
{
    _repository.updateAcknowledged(riskEventId, acknowledged);
}

void RiskEventService::deleteRiskEvent(const int riskEventId)
{
    _repository.deleteById(riskEventId);
}

void RiskEventService::updateState(const RiskEventData& riskEventData)
{
    _stateManager.setRiskEventData(riskEventData);
}