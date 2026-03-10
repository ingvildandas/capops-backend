#pragma once

#include <vector>

#include "Models/RiskEvent.hpp"
#include "Models/SectorSummary.hpp"
#include "Models/Track.hpp"

struct FlightDataState {
    int totalAircraftsCount;
    std::vector<RiskEvent> riskEvents;
    std::vector<SectorSummary> sectorSummaries;
    std::vector<Track> tracks;
};