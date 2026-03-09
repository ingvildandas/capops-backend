#pragma once

#include <vector>

class RiskEvent;
class SectorSummary;
class Track;

struct FlightDataState {
    int totalAircraftsCount;
    std::vector<RiskEvent> riskEvents;
    std::vector<SectorSummary> sectorSummaries;
    std::vector<Track> tracks;
};