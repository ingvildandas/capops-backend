#pragma once

#include <vector>

#include "Models/Metadata.hpp"

class RiskEventData;
class SectorSummaryData;
class TrackData;

class FlightDataDto
{
public:
    FlightDataDto
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
