#include <vector>

#include "Managers/FlightDataStateManager.hpp"
#include "Exceptions/EntityModelException.hpp"
#include "Models/FlightData.hpp"
#include "Models/Metadata.hpp"
#include "Models/RiskEventData.hpp"
#include "Models/SectorSummaryData.hpp"
#include "Models/TrackData.hpp"
#include "Structs/FlightDataStructs.hpp"

FlightDataStateManager::FlightDataStateManager()
{
    _state = std::make_unique<FlightDataState>();
}

FlightData FlightDataStateManager::getState()
{
    if 
    (
        !_state->metadata || 
        !_state->riskEventData || 
        !_state->sectorSummaryData || 
        !_state->trackData
    ) 
    {
        throw EntityModelException("FlightDataState is not fully initialized.");
    }

    return FlightData
    (
        *_state->metadata, 
        *_state->riskEventData, 
        *_state->sectorSummaryData, 
        *_state->trackData
    );
}

void FlightDataStateManager::setMetadata(const Metadata& metadata)
{
    _state->metadata = std::make_unique<Metadata>(metadata);
}

void FlightDataStateManager::setRiskEventData(const RiskEventData& riskEventData)
{
    _state->riskEventData = std::make_unique<RiskEventData>(riskEventData);
}

void FlightDataStateManager::setSectorSummaryData(const SectorSummaryData& sectorSummaryData)
{
    _state->sectorSummaryData = std::make_unique<SectorSummaryData>(sectorSummaryData);
}

void FlightDataStateManager::setTrackData(const TrackData& trackData)
{
    _state->trackData = std::make_unique<TrackData>(trackData);
}

void FlightDataStateManager::resetState()
{
    _state = std::make_unique<FlightDataState>();
}