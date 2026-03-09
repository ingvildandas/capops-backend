#pragma once

#include <vector>

#include "Structs/FlightDataStructs.hpp"

class FlightDataDto;
class RiskEvent;
class SectorSummary;
class Track;

class FlightDataStateManager
{
public:
    FlightDataStateManager();

    FlightDataDto getState();

    void setRiskEvents(std::vector<RiskEvent>& riskEvents);
    void setSectorSummaries(std::vector<SectorSummary>& sectorSummaries);
    void setTracks(std::vector<Track>& tracks);

private:
    FlightDataState _state;
};

