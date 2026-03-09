#pragma once

#include <memory>
#include <vector>

#include "Structs/FlightDataStructs.hpp"

class FlightDataDto;
class RiskEvent;
class SectorSummary;
class Track;

class FlightDataStateManager
{
public:
    FlightDataStateManager() = default;

    FlightDataDto getState();

    void setRiskEvents(std::vector<RiskEvent>& riskEvents);
    void setSectorSummaries(std::vector<SectorSummary>& sectorSummaries);
    void setTracks(std::vector<Track>& tracks);

private:
    std::unique_ptr<FlightDataState> _state = nullptr;
};

