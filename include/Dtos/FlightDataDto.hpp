#pragma once

#include <vector>

#include "Models/Metadata.hpp"

class RiskEvent;
class SectorSummary;
class Track;

class FlightDataDto
{
public:
    FlightDataDto
    (
        const Metadata& metadata,
        const std::vector<RiskEvent>& riskEvents,
        const std::vector<SectorSummary>& sectorSummaries,
        const std::vector<Track>& tracks
    );

    Metadata getMetadata() const;
    std::vector<RiskEvent> getRiskEvents() const;
    std::vector<SectorSummary> getSectorSummaries() const;
    std::vector<Track> getTracks() const;

private:
    Metadata _metadata;
    std::vector<RiskEvent> _riskEvents;
    std::vector<SectorSummary> _sectorSummaries;
    std::vector<Track> _tracks;
};
