#pragma once

#include <vector>

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
    struct FlightDataState {
        int totalAircraftsCount;
        std::vector<RiskEvent> riskEvents;
        std::vector<SectorSummary> sectorSummaries;
        std::vector<Track> tracks;
    };
};

