#include <vector>

#include "Dtos/FlightDataDto.hpp"
#include "Models/Metadata.hpp"
#include "Models/RiskEventData.hpp"
#include "Models/SectorSummaryData.hpp"
#include "Models/TrackData.hpp"

FlightDataDto::FlightDataDto
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

Metadata FlightDataDto::getMetadata() const
{
    return _metadata;
} 

RiskEventData FlightDataDto::getRiskEventData() const
{
    return _riskEventData;
}

SectorSummaryData FlightDataDto::getSectorSummaryData() const
{
    return _sectorSummaryData;
}

TrackData FlightDataDto::getTrackData() const
{
    return _trackData;
}
