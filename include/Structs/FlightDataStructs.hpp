#pragma once

#include <memory>
#include <vector>

#include "Models/Metadata.hpp"
#include "Models/RiskEventData.hpp"
#include "Models/SectorSummaryData.hpp"
#include "Models/TrackData.hpp"

struct FlightDataState {
    std::unique_ptr<Metadata> metadata = nullptr;
    std::unique_ptr<RiskEventData> riskEventData = nullptr;
    std::unique_ptr<SectorSummaryData> sectorSummaryData = nullptr;
    std::unique_ptr<TrackData> trackData = nullptr;
};