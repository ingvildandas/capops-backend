#include <catch2/catch_test_macros.hpp>

#include <vector>

#include <QDateTime>

#include "Managers/FlightDataStateManager.hpp"
#include "Models/FlightData.hpp"
#include "Models/RiskEvent.hpp"
#include "Models/RiskEventData.hpp"
#include "Models/SectorSummaryData.hpp"
#include "Models/TrackData.hpp"
#include "Repositories/IRiskEventRepository.hpp"
#include "Services/RiskEventService.hpp"

class MockRiskEventRepository : public IRiskEventRepository {
public:
    RiskEvent selectById(int) override { return {}; }
    std::vector<RiskEvent> selectMultipleByCount(int) override { return {}; }
    std::vector<RiskEvent> selectMultipleByAcknowledged(int,bool) override { return {}; }
    std::vector<RiskEvent> selectMultipleByTimestamps(int,const QDateTime&,const QDateTime&) override { return {}; }
    std::vector<RiskEvent> selectMultipleByParameters(int,bool,const QDateTime&,const QDateTime&) override { return {}; }
    void insert(const RiskEvent&) override {}
    void insertMultiple(const std::vector<RiskEvent>&) override {}
    void updateAcknowledged(const int riskEventId, const bool acknowledged) override {}
    void updateMultipleAcknowledged(const std::vector<int>&) override {}
    void deleteById(int) override {}
};

TEST_CASE("Risk events are merged correctly", "[RiskEventService]")
{
    // Arrange 

    MockRiskEventRepository repo;
    RiskEventService svc(repo);
    FlightDataStateManager stateManager;

    RiskEvent riskEvent1
    (
        1, 
        0, 
        false, 
        "NORMAL", 
        QDateTime::fromString("2024-06-01T12:00:00.000Z"),
        QDateTime(),
        "Test risk event 1"
    );
    
    RiskEvent riskEvent2
    (
        2, 
        0, 
        false, 
        "CONGESTED", 
        QDateTime::fromString("2024-06-01T12:10:00.000Z"),
        QDateTime(),
        "Test risk event 2"
    );
    
    RiskEvent riskEvent3
    (
        3, 
        0, 
        false, 
        "AT_RISK", 
        QDateTime::fromString("2024-06-01T12:20:00.000Z"),
        QDateTime(),
        "Test risk event 3"
    );

    std::vector<RiskEvent> existingRiskEvents;
    existingRiskEvents.push_back(riskEvent1);
    existingRiskEvents.push_back(riskEvent2);
    RiskEventData existingRiskEventData(2, existingRiskEvents);

    std::vector<RiskEvent> incomingRiskEvents;
    existingRiskEvents.push_back(riskEvent3);
    RiskEventData incomingRiskEventData(1, incomingRiskEvents);
    
    Metadata metadata(QDateTime::fromString("2024-06-01T12:20:00.000Z"));
    SectorSummaryData sectorSummaryData(2, 2, -180.0, 180.0, -90.0, 90.0, {});
    TrackData trackData(0, "WGS84", {});

    stateManager.setMetadata(metadata);
    stateManager.setRiskEventData(existingRiskEventData);
    stateManager.setSectorSummaryData(sectorSummaryData);
    stateManager.setTrackData(trackData);

    // Act
    svc.updateState(incomingRiskEventData, stateManager);

    // Assert
    const auto updatedMergedRiskEvents = 
        stateManager.getState().getRiskEventData().getMergedRiskEvents();
    
    REQUIRE(updatedMergedRiskEvents.size() == 1);

    const auto& mergedEvents = updatedMergedRiskEvents[0].getRiskEvents();
    REQUIRE(mergedEvents.size() == 3);

    REQUIRE
    (
        std::find_if
        (
            mergedEvents.begin(), 
            mergedEvents.end(),
            [&](const RiskEvent& r){ return r.getRiskEventId()==1; }
        ) != mergedEvents.end()
    );

    REQUIRE
    (
        std::find_if
        (
            mergedEvents.begin(), 
            mergedEvents.end(),
            [&](const RiskEvent& r){ return r.getRiskEventId()==2; }
        ) != mergedEvents.end()
    );
    
    REQUIRE
    (
        std::find_if
        (
            mergedEvents.begin(), 
            mergedEvents.end(),
            [&](const RiskEvent& r){ return r.getRiskEventId()==3; }
        ) != mergedEvents.end()
    );
}