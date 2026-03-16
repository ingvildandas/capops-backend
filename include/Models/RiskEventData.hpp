#pragma once

#include <vector>

#include "Models/RiskEvent.hpp"
#include "Models/MergedRiskEvent.hpp"

class RiskEventData
{
public:
    RiskEventData
    (
        const int riskEventCount,
        const std::vector<RiskEvent>& riskEvents
    );

    int getRiskEventCount() const;
    std::vector<RiskEvent> getRiskEvents() const;
    std::vector<MergedRiskEvent> getMergedRiskEvents() const;

private:
    int _riskEventCount;
    std::vector<RiskEvent> _riskEvents;
    std::vector<MergedRiskEvent> _mergedRiskEvents;

private:
    void mergeRiskEvents(); 
};
