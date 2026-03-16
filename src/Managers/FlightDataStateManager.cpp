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

void FlightDataStateManager::setRiskEvents(const std::vector<RiskEvent>& riskEvents)
{}

void FlightDataStateManager::setSectorSummaries(const std::vector<SectorSummary>& sectorSummaries)
{}

void FlightDataStateManager::setTracks(const std::vector<Track>& tracks)
{}
