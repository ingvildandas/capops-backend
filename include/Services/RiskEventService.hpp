#pragma once

#include <chrono>
#include <vector>

#include "Repositories/IRiskEventRepository.hpp"
#include "Managers/FlightDataStateManager.hpp"

class RiskEvent;

class RiskEventService 
{
public:
    explicit RiskEventService
    (
        IRiskEventRepository& repository, 
        FlightDataStateManager& stateManager
    );

    RiskEvent getRiskEvent(const int riskEventId);
    std::vector<const RiskEvent> getMostRecentRiskEvents(const int count);
    std::vector<const RiskEvent> getRiskEventsBetween
    (
        const std::chrono::system_clock::time_point& startTimestamp,
        const std::chrono::system_clock::time_point& endTimestamp
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