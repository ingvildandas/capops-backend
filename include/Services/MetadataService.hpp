#pragma once

#include <vector>

#include "Managers/FlightDataStateManager.hpp"

class MetadataService
{
public:
    MetadataService() = default;

    void updateState
    (
        const Metadata& metadata,
        FlightDataStateManager& stateManager
    );
};