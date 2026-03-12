#include "Services/TrackService.hpp"
#include "Managers/FlightDataStateManager.hpp"

TrackService::TrackService(
    FlightDataStateManager& stateManager
)
    : _stateManager(stateManager)
{}

void TrackService::updateState
(
    const std::vector<Track>& tracks
)
{}