#pragma once

#include <vector>

#include "Models/Metadata.hpp"
#include "Models/RiskEventData.hpp"
#include "Models/SectorSummaryData.hpp"
#include "Models/TrackData.hpp"

struct FlightDataState {
    Metadata metadata;
    RiskEventData riskEventData;
    SectorSummaryData sectorSummaryData;
    TrackData trackData;
};