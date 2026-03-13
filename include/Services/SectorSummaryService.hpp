#pragma once

#include <vector>

class SectorSummary;

#include "Managers/FlightDataStateManager.hpp"

class SectorSummaryService
{
public:
    SectorSummaryService(FlightDataStateManager& stateManager);

    void updateState(const std::vector<SectorSummary>& sectorSummaries);

private:
    FlightDataStateManager& _stateManager;
};