#include <vector>

#include "Dtos/FlightDataDto.hpp"
#include "Managers/FlightDataStateManager.hpp"
#include "Models/RiskEvent.hpp"
#include "Models/SectorSummary.hpp"
#include "Models/Track.hpp"
#include "Structs/FlightDataStructs.hpp"

FlightDataDto FlightDataStateManager::getState()
{
    return FlightDataDto
    (
        _state->metadata, 
        _state->riskEventData, 
        _state->sectorSummaryData, 
        _state->trackData
    );
}

void FlightDataStateManager::setMetadata(const Metadata& metadata)
{}

void FlightDataStateManager::setRiskEventData(const RiskEventData& riskEventData)
{}

void FlightDataStateManager::setSectorSummaryData(const SectorSummaryData& sectorSummaryData)
{}

void FlightDataStateManager::setTrackData(const TrackData& trackData)
{}
