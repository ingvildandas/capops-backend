#pragma once

#include <memory>
#include <vector>

#include "Structs/FlightDataStructs.hpp"

class FlightDataDto;
class RiskEventData;
class SectorSummaryData;
class TrackData;

class FlightDataStateManager
{
public:
    FlightDataStateManager() = default;

    FlightDataDto getState();

    void setMetadata(const Metadata& metadata);
    void setRiskEventData(const RiskEventData& riskEventData);
    void setSectorSummaryData(const SectorSummaryData& sectorSummaryData);
    void setTrackData(const TrackData& trackData);

private:
    std::unique_ptr<FlightDataState> _state = nullptr;
};

