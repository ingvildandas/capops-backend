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
        _state->totalAircraftsCount, 
        _state->riskEvents, 
        _state->sectorSummaries, 
        _state->tracks
    );
}

void FlightDataStateManager::setRiskEvents(std::vector<RiskEvent>& riskEvents)
{}

void FlightDataStateManager::setSectorSummaries(std::vector<SectorSummary>& sectorSummaries)
{}

void FlightDataStateManager::setTracks(std::vector<Track>& tracks)
{}
