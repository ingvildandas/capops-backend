#include "Services/MetadataService.hpp"
#include "Managers/FlightDataStateManager.hpp"
#include "Models/Metadata.hpp"

MetadataService::MetadataService(FlightDataStateManager& stateManager)
    : _stateManager(stateManager)
{}

void MetadataService::updateState(const Metadata& metadata)
{
    _stateManager.setMetadata(metadata);
}