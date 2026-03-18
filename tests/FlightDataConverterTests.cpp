#include <catch2/catch_test_macros.hpp>

#include <QDateTime>
#include <QString>

#include "Proto/FlightData.hpp"
#include "Converters/FlightDataConverter.hpp"

TEST_CASE("Deserialize valid FlightDataProto", "[FlightDataConverter]")
{
    // Arrange

    FlightDataProto proto;

    proto.mutable_metadata->set_version(1);
    proto.mutable_metadata->set_timestamp("2024-06-01T12:00:00.000Z");

    auto* riskEventDataProto = proto.mutable_riskeventdata();
    riskEventDataProto->set_riskeventcount(1);

    auto* riskEventProto = riskEventDataProto->add_riskevents();
    riskEventProto->set_riskeventid(123);
    riskEventProto->set_riskseverity("NORMAL");
    riskEventProto->set_sectorid(5);
    riskEventProto->set_createdtimestamp("2024-06-01T12:00:00.000Z");
    riskEventProto->set_acknowledgedtimestamp("2024-06-01T12:05:00.000Z");
    riskEventProto->set_message("Test risk event");
    riskEventProto->set_acknowledged(false);

    auto* sectorSummaryDataProto = proto.mutable_sectorsummarydata();
    sectorSummaryDataProto->set_rowscount(2);
    sectorSummaryDataProto->set_columnscount(2);
    sectorSummaryDataProto->set_minlongitude(-180.0);
    sectorSummaryDataProto->set_maxlongitude(180.0);
    sectorSummaryDataProto->set_minlatitude(-90.0);
    sectorSummaryDataProto->set_maxlatitude(90.0);

    auto* sectorSummaryProto1 = sectorSummaryDataProto->add_sectorsummaries();
    sectorSummaryProto1->set_sectorid(0);
    sectorSummaryProto1->set_row(0);
    sectorSummaryProto1->set_column(0);
    sectorSummaryProto1->set_weatherseverity("NORMAL");
    sectorSummaryProto1->set_riskseverity("NORMAL");
    sectorSummaryProto1->set_localaircraftcount(0);
    sectorSummaryProto1->set_localaircraftbasecapacity(10);
    sectorSummaryProto1->set_localaircrafteffectivecapacity(8);

    auto* sectorSummaryProto2 = sectorSummaryDataProto->add_sectorsummaries();
    sectorSummaryProto2->set_sectorid(1);
    sectorSummaryProto2->set_row(0);
    sectorSummaryProto2->set_column(1);
    sectorSummaryProto2->set_weatherseverity("NORMAL");
    sectorSummaryProto2->set_riskseverity("NORMAL");
    sectorSummaryProto2->set_localaircraftcount(1);
    sectorSummaryProto2->set_localaircraftbasecapacity(5);
    sectorSummaryProto2->set_localaircrafteffectivecapacity(4);

    auto* sectorSummaryProto3 = sectorSummaryDataProto->add_sectorsummaries();
    sectorSummaryProto3->set_sectorid(2);
    sectorSummaryProto3->set_row(1);
    sectorSummaryProto3->set_column(0);
    sectorSummaryProto3->set_weatherseverity("NORMAL");
    sectorSummaryProto3->set_riskseverity("NORMAL");
    sectorSummaryProto3->set_localaircraftcount(0);
    sectorSummaryProto3->set_localaircraftbasecapacity(4);
    sectorSummaryProto3->set_localaircrafteffectivecapacity(3);

    auto* sectorSummaryProto4 = sectorSummaryDataProto->add_sectorsummaries();
    sectorSummaryProto4->set_sectorid(3);
    sectorSummaryProto4->set_row(1);
    sectorSummaryProto4->set_column(1);
    sectorSummaryProto4->set_weatherseverity("NORMAL");
    sectorSummaryProto4->set_riskseverity("NORMAL");
    sectorSummaryProto4->set_localaircraftcount(0);
    sectorSummaryProto4->set_localaircraftbasecapacity(2);
    sectorSummaryProto4->set_localaircrafteffectivecapacity(1);

    auto* trackDataProto = proto.mutable_trackdata();
    trackDataProto->set_totalaircraftcount(1);
    trackDataProto->set_coordinatesystem("WGS84");

    auto* trackProto = trackDataProto->add_tracks();

    auto* positionProto = trackProto->mutable_position();
    positionProto->set_latitudedegrees(40.7128);
    positionProto->set_longitudedegrees(-74.0060);
    positionProto->set_altitudefeet(30000);

    auto* velocityProto = trackProto->mutable_velocity();
    velocityProto->set_groundspeedknots(450);
    velocityProto->set_verticalspeedfeetperminute(0);

    trackProto->set_icao24("ABCD1234");
    trackProto->set_timestamp("2024-06-01T12:00:00.000Z");
    trackProto->set_position(positionProto);
    trackProto->set_velocity(velocityProto);
    trackProto->set_headingdegrees(90);
    trackProto->set_groundtrackDegrees(90);

    // Act

    std::string serializedData;
    proto.SerializeToString(&serializedData);
    FlightData deserializedData = FlightDataConverter::fromProto(serializedData);

    // Assert

    REQUIRE(deserializedData.getMetadata().getVersion() == 1);
    REQUIRE
    (
        deserializedData.getMetadata().getTimestamp() == 
        QDateTime::fromString("2024-06-01T12:00:00.000Z", Qt::ISODate)
    );

    REQUIRE(deserializedData.getRiskEventData().getRiskEventCount() == 1);
    REQUIRE(deserializedData.getRiskEventData().getRiskEvents().size() == 1);

    const auto& riskEvent = deserializedData.getRiskEventData().getRiskEvents()[0];
    REQUIRE(riskEvent.getRiskEventId() == 123);
    REQUIRE(riskEvent.getRiskSeverity() == "NORMAL");
    REQUIRE(riskEvent.getSectorId() == 5);
    REQUIRE
    (
        riskEvent.getCreatedTimestamp() == 
        QDateTime::fromString("2024-06-01T12:00:00.000Z", Qt::ISODate)
    );
    REQUIRE
    (
        riskEvent.getAcknowledgedTimestamp() == 
        QDateTime::fromString("2024-06-01T12:05:00.000Z", Qt::ISODate)
    );
    REQUIRE(riskEvent.getMessage() == "Test risk event");
    REQUIRE(riskEvent.isAcknowledged() == false);

    REQUIRE(deserializedData.getSectorSummaryData().getRowsCount() == 2);
    REQUIRE(deserializedData.getSectorSummaryData().getColumnsCount() == 2);
    REQUIRE(deserializedData.getSectorSummaryData().getMinLongitude() == -180.0);
    REQUIRE(deserializedData.getSectorSummaryData().getMaxLongitude() == 180.0);
    REQUIRE(deserializedData.getSectorSummaryData().getMinLatitude() == -90.0);
    REQUIRE(deserializedData.getSectorSummaryData().getMaxLatitude() == 90.0);
    REQUIRE(deserializedData.getSectorSummaryData().getSectorSummaries().size() == 4);

    const auto& sectorSummary1 = deserializedData.getSectorSummaryData().getSectorSummaries()[0];
    REQUIRE(sectorSummary1.getSectorId() == 0);
    REQUIRE(sectorSummary1.getRow() == 0);
    REQUIRE(sectorSummary1.getColumn() == 0);
    REQUIRE(sectorSummary1.getWeatherSeverity() == "NORMAL");
    REQUIRE(sectorSummary1.getRiskSeverity() == "NORMAL");
    REQUIRE(sectorSummary1.getLocalAircraftCount() == 0);
    REQUIRE(sectorSummary1.getLocalAircraftBaseCapacity() == 10);
    REQUIRE(sectorSummary1.getLocalAircraftEffectiveCapacity() == 8);

    REQUIRE(deserializedData.getTrackData().getTotalAircraftCount() == 1);
    REQUIRE(deserializedData.getTrackData().getCoordinateSystem() == "WGS84");
    REQUIRE(deserializedData.getTrackData().getTracks().size() == 1);

    const auto& track = deserializedData.getTrackData().getTracks()[0];
    REQUIRE(track.getIcao24() == "ABCD1234");
    REQUIRE
    (
        track.getTimestamp() == 
        QDateTime::fromString("2024-06-01T12:00:00.000Z", Qt::ISODate)
    );
    REQUIRE(track.getPosition().getLatitudeDegrees() == 40.7128);
    REQUIRE(track.getPosition().getLongitudeDegrees() == -74.0060);
    REQUIRE(track.getPosition().getAltitudeFeet() == 30000);
    REQUIRE(track.getVelocity().getGroundSpeedKnots() == 450);
    REQUIRE(track.getVelocity().getVerticalSpeedFeetPerMinute() == 0);
    REQUIRE(track.getHeadingDegrees() == 90);
    REQUIRE(track.getGroundTrackDegrees() == 90);
}
