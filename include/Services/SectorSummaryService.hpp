#pragma once

#include <vector>

class SectorSummary;
class SectorSummaryData;

#include "Managers/FlightDataStateManager.hpp"

class SectorSummaryService
{
public:
    SectorSummaryService(FlightDataStateManager& stateManager);

    void updateState(const SectorSummaryData& sectorSummaryData);

private:
    FlightDataStateManager& _stateManager;
};