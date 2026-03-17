#include <vector>

#include "Models/FlightData.hpp"
#include "Managers/FlightDataStateManager.hpp"
#include "Models/RiskEvent.hpp"
#include "Models/SectorSummary.hpp"
#include "Models/Track.hpp"
#include "Structs/FlightDataStructs.hpp"

FlightDataStateManager::FlightDataStateManager()
{
    _state = std::make_unique<FlightDataState>();
}

FlightData FlightDataStateManager::getState()
{
    return FlightData
    (
        _state->metadata, 
        _state->riskEventData, 
        _state->sectorSummaryData, 
        _state->trackData
    );
}

void FlightDataStateManager::setMetadata(const Metadata& metadata)
{
    _state->metadata = metadata;
}

void FlightDataStateManager::setRiskEventData(const RiskEventData& riskEventData)
{
    _state->riskEventData = riskEventData;
}

void FlightDataStateManager::setSectorSummaryData(const SectorSummaryData& sectorSummaryData)
{
    _state->sectorSummaryData = sectorSummaryData;
}

void FlightDataStateManager::setTrackData(const TrackData& trackData)
{
    _state->trackData = trackData;
}

void FlightDataStateManager::resetState()
{
    _state = std::make_unique<FlightDataState>();
}