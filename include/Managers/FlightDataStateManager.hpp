#pragma once

#include <memory>
#include <vector>

#include "Structs/FlightDataStructs.hpp"

class FlightData;
class RiskEventData;
class SectorSummaryData;
class TrackData;

class FlightDataStateManager
{
public:
    FlightDataStateManager();

    FlightData getState();

    void setMetadata(const Metadata& metadata);
    void setRiskEventData(const RiskEventData& riskEventData);
    void setSectorSummaryData(const SectorSummaryData& sectorSummaryData);
    void setTrackData(const TrackData& trackData);

    void resetState();

private:
    std::unique_ptr<FlightDataState> _state = nullptr;
};

