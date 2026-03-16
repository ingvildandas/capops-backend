#include "Services/TrackService.hpp"
#include "Managers/FlightDataStateManager.hpp"
#include "Models/TrackData.hpp"

TrackService::TrackService(
    FlightDataStateManager& stateManager
)
    : _stateManager(stateManager)
{}

void TrackService::updateState
(
    const TrackData& trackData
)
{}