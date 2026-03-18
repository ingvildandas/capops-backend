#pragma once

#include <vector>

class TrackData;

#include "Managers/FlightDataStateManager.hpp"

class TrackService
{
public:
    TrackService() = default;

    void updateState
    (
        const TrackData& trackData,
        FlightDataStateManager& stateManager
    );
};