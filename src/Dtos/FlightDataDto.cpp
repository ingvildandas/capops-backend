#include <vector>

#include "Dtos/FlightDataDto.hpp"
#include "Models/RiskEvent.hpp"
#include "Models/SectorSummary.hpp"
#include "Models/Track.hpp"

FlightDataDto::FlightDataDto
(
    const int totalAircraftsCount,
    std::vector<RiskEvent>& riskEvents,
    std::vector<SectorSummary>& sectorSummaries,
    std::vector<Track>& tracks
)
    :
    _totalAircraftsCount(totalAircraftsCount),
    _riskEvents(riskEvents),
    _sectorSummaries(sectorSummaries),
    _tracks(tracks)
{}

int FlightDataDto::getTotalAircraftsCount() const
{
    return _totalAircraftsCount;
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
