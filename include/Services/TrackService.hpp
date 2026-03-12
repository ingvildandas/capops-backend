#pragma once

#include <vector>

class Track;

#include "Managers/FlightDataStateManager.hpp"

class TrackService
{
public:
    TrackService(FlightDataStateManager& stateManager);

    void updateState(std::vector<Track>& tracks);

private:
    FlightDataStateManager& _stateManager;
};