#pragma once

#include <vector>

#include "Repositories/IRiskEventRepository.hpp"
#include "Managers/FlightDataStateManager.hpp"

class RiskEvent;
class RiskEventData;
class QDateTime;

class RiskEventService 
{
public:
    explicit RiskEventService(IRiskEventRepository& repository);

    RiskEvent getRiskEvent(const int riskEventId);
    std::vector<RiskEvent> getMultipleRiskEvents(const int count);
    std::vector<RiskEvent> getMultipleRiskEvents
    (
        const int count, 
        const bool acknowledged
    );
    std::vector<RiskEvent> getMultipleRiskEvents
    (
        const int count,
        const QDateTime& from,
        const QDateTime& to
    );
    std::vector<RiskEvent> getMultipleRiskEvents
    (
        const int count,
        const bool acknowledged,
        const QDateTime& from,
        const QDateTime& to
    );

    void registerRiskEvent(const RiskEvent& riskEvent);
    void registerMultipleRiskEvents(const std::vector<RiskEvent>& riskEvents);
    void updateAcknowledged(const int riskEventId, const bool acknowledged);
    void deleteRiskEvent(const int riskEventId);

    void updateState
    (
        const RiskEventData& riskEventData,
        FlightDataStateManager& stateManager
    );

private:
    IRiskEventRepository& _repository;
};