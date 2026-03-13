#pragma once

#include <vector>

class RiskEvent;
class SectorSummary;
class Track;

class FlightDataDto
{
public:
    FlightDataDto
    (
        const int totalAircraftsCount,
        std::vector<RiskEvent>& riskEvents,
        std::vector<SectorSummary>& sectorSummaries,
        std::vector<Track>& tracks
    );

    int getTotalAircraftsCount() const;
    std::vector<RiskEvent> getRiskEvents() const;
    std::vector<SectorSummary> getSectorSummaries() const;
    std::vector<Track> getTracks() const;

private:
    int _totalAircraftsCount;
    std::vector<RiskEvent> _riskEvents;
    std::vector<SectorSummary> _sectorSummaries;
    std::vector<Track> _tracks;
};
