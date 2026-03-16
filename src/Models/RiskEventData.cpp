#include <unordered_map>
#include <vector>

#include "Models/RiskEventData.hpp";
#include "Models/RiskEvent.hpp";
#include "Models/MergedRiskEvent.hpp";

RiskEventData::RiskEventData
(
    const int riskEventCount,
    const std::vector<RiskEvent>& riskEvents
)
    : _riskEventCount(riskEventCount)
{
    mergeRiskEvents();
}

int RiskEventData::getRiskEventCount() const
{
    return _riskEventCount;
}

std::vector<RiskEvent> RiskEventData::getRiskEvents() const
{
    return _riskEvents;
}

std::vector<MergedRiskEvent> RiskEventData::getMergedRiskEvents() const
{
    return _mergedRiskEvents;
}

void RiskEventData::mergeRiskEvents()
{
    std::unordered_map<int, std::vector<RiskEvent>> riskEventsPerSectorMap;

    for (RiskEvent riskEvent : _riskEvents)
    {
        int sectorId = riskEvent.getSectorId();
        riskEventsPerSectorMap[sectorId].push_back(riskEvent);
    }

    std::vector<MergedRiskEvent> mergedRiskEvents;
    mergedRiskEvents.reserve(riskEventsPerSectorMap.size());
    for (const auto& [sectorId, riskEvents] : riskEventsPerSectorMap)
    {
        mergedRiskEvents.push_back(MergedRiskEvent(sectorId, riskEvents));
    }

    _mergedRiskEvents = mergedRiskEvents;
}