#pragma once

#include <vector>

class SectorSummary;

#include "Managers/FlightDataStateManager.hpp"

class SectorSummaryService
{
public:
    SectorSummaryService(FlightDataStateManager& stateManager);

    void updateState(std::vector<const SectorSummary*>& sectorSummaries);

private:
    FlightDataStateManager& _stateManager;
};