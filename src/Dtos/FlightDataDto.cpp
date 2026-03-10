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
{}

int FlightDataDto::getTotalAircraftsCount() const
{
    return 0;
} 

std::vector<RiskEvent> FlightDataDto::getRiskEvents() const
{
    return std::vector<RiskEvent>{};
}

std::vector<SectorSummary> FlightDataDto::getSectorSummaries() const
{
    return std::vector<SectorSummary>{};
}

std::vector<Track> FlightDataDto::getTracks() const
{
    return std::vector<Track>{};
}
