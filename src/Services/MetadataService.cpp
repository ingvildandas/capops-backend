#include "Services/MetadataService.hpp"
#include "Managers/FlightDataStateManager.hpp"
#include "Models/Metadata.hpp"

void MetadataService::updateState
(
    const Metadata& metadata,
    FlightDataStateManager& stateManager
)
{
    stateManager.setMetadata(metadata);
}