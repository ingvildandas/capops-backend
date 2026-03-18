#include "Services/TrackService.hpp"
#include "Managers/FlightDataStateManager.hpp"
#include "Models/TrackData.hpp"

void TrackService::updateState
(
    const TrackData& trackData,
    FlightDataStateManager& stateManager
)
{
    stateManager.setTrackData(trackData);
}