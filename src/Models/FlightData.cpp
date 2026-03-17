#include <vector>

#include "Models/FlightData.hpp"
#include "Models/Metadata.hpp"
#include "Models/RiskEventData.hpp"
#include "Models/SectorSummaryData.hpp"
#include "Models/TrackData.hpp"

FlightData::FlightData
(
    const Metadata& metadata,
    const RiskEventData& riskEventData,
    const SectorSummaryData& sectorSummaryData,
    const TrackData& trackData
)
    :
    _metadata(metadata),
    _riskEventData(riskEventData),
    _sectorSummaryData(sectorSummaryData),
    _trackData(trackData)
{}

Metadata FlightData::getMetadata() const
{
    return _metadata;
} 

RiskEventData FlightData::getRiskEventData() const
{
    return _riskEventData;
}

SectorSummaryData FlightData::getSectorSummaryData() const
{
    return _sectorSummaryData;
}

TrackData FlightData::getTrackData() const
{
    return _trackData;
}
