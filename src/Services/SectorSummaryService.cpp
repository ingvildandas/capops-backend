#include "Services/SectorSummaryService.hpp"
#include "Managers/FlightDataStateManager.hpp"
#include "Models/SectorSummaryData.hpp"

SectorSummaryService::SectorSummaryService(
    FlightDataStateManager& stateManager
)
    : _stateManager(stateManager)
{}

void SectorSummaryService::updateState
(
    const SectorSummaryData& sectorSummaries
)
{
    _stateManager.setSectorSummaryData(sectorSummaries);
}