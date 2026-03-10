#pragma once

#include <vector>

#include "Repositories/IRiskEventRepository.hpp"
#include "Managers/FlightDataStateManager.hpp"

class RiskEvent;
class QTimeZone;

class RiskEventService 
{
public:
    explicit RiskEventService
    (
        IRiskEventRepository& repository, 
        FlightDataStateManager& stateManager
    );

    RiskEvent getRiskEvent(const int riskEventId);
    std::vector<const RiskEvent> getMultipleRiskEvents
    (
        const int count,
        const bool acknowledged,
        const QTimeZone& from,
        const QTimeZone& to
    );

    void registerRiskEvent(const RiskEvent& riskEvent);
    void registerMultipleRiskEvents(std::vector<const RiskEvent*>& riskEvents);
    void updateAcknowledged(const int riskEventId, const bool acknowledged);
    void deleteRiskEvent(const int riskEventId);

    void updateState(std::vector<const RiskEvent*>& riskEvents);
private:
    IRiskEventRepository& _repository;
    FlightDataStateManager& _stateManager;
};