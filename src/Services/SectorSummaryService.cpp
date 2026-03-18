#include "Services/SectorSummaryService.hpp"
#include "Managers/FlightDataStateManager.hpp"
#include "Models/SectorSummaryData.hpp"

void SectorSummaryService::updateState
(
    const SectorSummaryData& sectorSummaries,
    FlightDataStateManager& stateManager
)
{
    stateManager.setSectorSummaryData(sectorSummaries);
}