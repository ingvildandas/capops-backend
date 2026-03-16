#pragma once

#include <vector>

#include "Managers/FlightDataStateManager.hpp"

class MetadataService
{
public:
    MetadataService(FlightDataStateManager& stateManager);

    void updateState(const Metadata& metadata);

private:
    FlightDataStateManager& _stateManager;
};