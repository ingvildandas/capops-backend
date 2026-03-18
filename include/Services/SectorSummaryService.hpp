#pragma once

#include <vector>

class SectorSummary;
class SectorSummaryData;

#include "Managers/FlightDataStateManager.hpp"

class SectorSummaryService
{
public:
    SectorSummaryService() = default;

    void updateState
    (
        const SectorSummaryData& sectorSummaryData,
        FlightDataStateManager& stateManager
    );
};