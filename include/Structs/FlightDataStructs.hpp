#pragma once

#include <vector>

#include "Models/Metadata.hpp"
#include "Models/RiskEvent.hpp"
#include "Models/SectorSummary.hpp"
#include "Models/Track.hpp"

struct FlightDataState {
    Metadata metadata;
    std::vector<RiskEvent> riskEvents;
    std::vector<SectorSummary> sectorSummaries;
    std::vector<Track> tracks;
};