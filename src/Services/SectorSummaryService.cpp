#include "Services/SectorSummaryService.hpp"
#include "Managers/FlightDataStateManager.hpp"

SectorSummaryService::SectorSummaryService(
    FlightDataStateManager& stateManager
)
    : _stateManager(stateManager)
{}

void SectorSummaryService::updateState
(
    const std::vector<SectorSummary>& sectorSummaries
)
{}