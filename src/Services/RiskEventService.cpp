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
    return RiskEvent(0, 0, false, "", QDateTime(), QDateTime(), "");
}

std::vector<RiskEvent> RiskEventService::getMultipleRiskEvents
(
    const int count,
    const bool acknowledged,
    const QDateTime& from,
    const QDateTime& to
)
{
    return std::vector<RiskEvent>{};
}

void RiskEventService::registerRiskEvent(const RiskEvent& riskEvent)
{}

void RiskEventService::registerMultipleRiskEvents(std::vector<const RiskEvent*>& riskEvents)
{}

void RiskEventService::updateAcknowledged(const int riskEventId, const bool acknowledged)
{}

void RiskEventService::deleteRiskEvent(const int riskEventId)
{}

void RiskEventService::updateState(const RiskEventData& riskEventData)
{}