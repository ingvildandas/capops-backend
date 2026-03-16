#pragma once

#include <vector>

class TrackData;

#include "Managers/FlightDataStateManager.hpp"

class TrackService
{
public:
    TrackService(FlightDataStateManager& stateManager);

    void updateState(const TrackData& trackData);

private:
    FlightDataStateManager& _stateManager;
};