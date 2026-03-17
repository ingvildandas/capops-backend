#pragma once

#include <vector>

#include "Models/Metadata.hpp"
#include "Models/RiskEventData.hpp"
#include "Models/SectorSummaryData.hpp"
#include "Models/TrackData.hpp"

class FlightData
{
public:
    FlightData
    (
        const Metadata& metadata,
        const RiskEventData& riskEventData,
        const SectorSummaryData& sectorSummaryData,
        const TrackData& trackData
    );

    Metadata getMetadata() const;
    RiskEventData getRiskEventData() const;
    SectorSummaryData getSectorSummaryData() const;
    TrackData getTrackData() const;

private:
    Metadata _metadata;
    RiskEventData _riskEventData;
    SectorSummaryData _sectorSummaryData;
    TrackData _trackData;
};
