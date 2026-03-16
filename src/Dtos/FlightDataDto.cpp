#include <vector>

#include "Dtos/FlightDataDto.hpp"
#include "Models/Metadata.hpp"
#include "Models/RiskEvent.hpp"
#include "Models/SectorSummary.hpp"
#include "Models/Track.hpp"

FlightDataDto::FlightDataDto
(
    const Metadata& metadata,
    const std::vector<RiskEvent>& riskEvents,
    const std::vector<SectorSummary>& sectorSummaries,
    const std::vector<Track>& tracks
)
    :
    _metadata(metadata),
    _riskEvents(riskEvents),
    _sectorSummaries(sectorSummaries),
    _tracks(tracks)
{}

Metadata FlightDataDto::getMetadata() const
{
    return _metadata;
} 

std::vector<RiskEvent> FlightDataDto::getRiskEvents() const
{
    return _riskEvents;
}

std::vector<SectorSummary> FlightDataDto::getSectorSummaries() const
{
    return _sectorSummaries;
}

std::vector<Track> FlightDataDto::getTracks() const
{
    return _tracks;
}
