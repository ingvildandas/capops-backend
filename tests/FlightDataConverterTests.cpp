#include <catch2/catch_test_macros.hpp>

#include <vector>

#include <QDateTime>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>

#include "Proto/FlightData.hpp"
#include "Converters/FlightDataConverter.hpp"
#include "Managers/EnvironmentManager.hpp"
#include "Models/FlightData.hpp"
#include "Models/Metadata.hpp"

TEST_CASE("Deserialize valid FlightDataProto", "[FlightDataConverter]")
{
    // Arrange

    FlightDataProto proto;

    proto.mutable_metadata()->set_version(1);
    proto.mutable_metadata()->set_timestamp("2024-06-01T12:00:00.000Z");

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
    trackProto->set_headingdegrees(90);
    trackProto->set_groundtrackdegrees(90);

    // Act

    std::string serializedData;
    proto.SerializeToString(&serializedData);
    FlightData deserializedData = FlightDataConverter::fromProto(proto);

    // Assert

    REQUIRE
    (
        deserializedData.getMetadata().getTimestamp() == 
        QDateTime::fromString("2024-06-01T12:00:00.000Z", Qt::ISODate)
    );

    REQUIRE(deserializedData.getRiskEventData().getRiskEventCount() == 1);
    REQUIRE(deserializedData.getRiskEventData().getRiskEvents().size() == 1);

    const auto riskEvent = deserializedData.getRiskEventData().getRiskEvents()[0];
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
    REQUIRE(riskEvent.getAcknowledged() == false);

    REQUIRE(deserializedData.getSectorSummaryData().getRowsCount() == 2);
    REQUIRE(deserializedData.getSectorSummaryData().getColumnsCount() == 2);
    REQUIRE(deserializedData.getSectorSummaryData().getMinLongitude() == -180.0);
    REQUIRE(deserializedData.getSectorSummaryData().getMaxLongitude() == 180.0);
    REQUIRE(deserializedData.getSectorSummaryData().getMinLatitude() == -90.0);
    REQUIRE(deserializedData.getSectorSummaryData().getMaxLatitude() == 90.0);
    REQUIRE(deserializedData.getSectorSummaryData().getSectorSummaries().size() == 4);

    const auto sectorSummary1 = deserializedData.getSectorSummaryData().getSectorSummaries()[0];
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

    const auto track = deserializedData.getTrackData().getTracks()[0];
    REQUIRE(track.getIcao24() == "ABCD1234");
    REQUIRE
    (
        track.getTimestamp() == 
        QDateTime::fromString("2024-06-01T12:00:00.000Z", Qt::ISODate)
    );
    REQUIRE(track.getPosition().latitudeDegrees == 40.7128);
    REQUIRE(track.getPosition().longitudeDegrees == -74.0060);
    REQUIRE(track.getPosition().altitudeFeet == 30000);
    REQUIRE(track.getVelocity().groundSpeedKnots == 450);
    REQUIRE(track.getVelocity().verticalSpeedFeetPerMinute == 0);
    REQUIRE(track.getHeadingDegrees() == 90);
    REQUIRE(track.getGroundTrackDegrees() == 90);
}

TEST_CASE("Serialize valid FlightData to JSON", "[FlightDataConverter]")
{
    // Arrange

    Metadata metadata
    (
        QDateTime::fromString("2024-06-01T12:00:00.000Z", Qt::ISODate)
    );

    RiskEvent riskEvent1
    (
        123,
        2,
        false,
        "NORMAL",
        QDateTime::fromString("2024-06-01T12:00:00.000Z", Qt::ISODate),
        QDateTime::fromString("2024-06-01T12:05:00.000Z", Qt::ISODate),
        "Test risk event"
    );

    RiskEvent riskEvent2
    (
        124,
        2,
        false,
        "AT_RISK",
        QDateTime::fromString("2024-06-01T12:10:00.000Z", Qt::ISODate),
        QDateTime::fromString("2024-06-01T12:15:00.000Z", Qt::ISODate),
        "Test risk event 2"
    );

    RiskEvent riskEvent3
    (
        125,
        2,
        false,
        "CONGESTED",
        QDateTime::fromString("2024-06-01T12:20:00.000Z", Qt::ISODate),
        QDateTime::fromString("2024-06-01T12:25:00.000Z", Qt::ISODate),
        "Test risk event 3"
    );

    std::vector<RiskEvent> riskEvents = { riskEvent1, riskEvent2, riskEvent3 };

    RiskEventData riskEventData(1, riskEvents);

    SectorSummary sectorSummary1(0, 0, 0, 0, 10, 8, "NORMAL", "NORMAL");
    SectorSummary sectorSummary2(1, 0, 1, 1, 5, 4, "NORMAL", "NORMAL");
    SectorSummary sectorSummary3(2, 1, 0, 0, 4, 3, "NORMAL", "NORMAL");
    SectorSummary sectorSummary4(3, 1, 1, 0, 2, 1, "NORMAL", "NORMAL");

    std::vector<SectorSummary> sectorSummaries = 
    {
        sectorSummary1,
        sectorSummary2,
        sectorSummary3,
        sectorSummary4
    };

    SectorSummaryData sectorSummaryData(2, 2, -180.0, 180.0, -90.0, 90.0, sectorSummaries);

    TrackPosition trackPosition{40.7128, -74.0060, 30000};
    TrackVelocity trackVelocity{450, 0};

    Track track
    (
        "ABCD1234",
        QDateTime::fromString("2024-06-01T12:00:00.000Z", Qt::ISODate),
        trackPosition,
        trackVelocity,
        90,
        90
    );

    TrackData trackData(1, "WGS84", { track });

    FlightData flightData(metadata, riskEventData, sectorSummaryData, trackData);

    // Act

    EnvironmentManager envManager(".env");
    QJsonObject json = FlightDataConverter::toJson(flightData, envManager);

    // Assert

    const auto metadataJson = json["metadata"].toObject();
    REQUIRE(metadataJson["timestamp"].toString() == "2024-06-01T12:00:00.000Z");
    REQUIRE(metadataJson["version"].toInt() == 1);

    const auto riskEventDataJson = json["riskEventData"].toObject();
    REQUIRE(riskEventDataJson["riskEventCount"].toInt() == 1);
    REQUIRE(riskEventDataJson["riskEvents"].toArray().size() == 3);
    REQUIRE(riskEventDataJson["mergedRiskEvents"].toArray().size() == 1);

    const auto riskEventJson1 = riskEventDataJson["riskEvents"].toArray()[0].toObject();
    REQUIRE(riskEventJson1["riskEventId"].toInt() == 123);
    REQUIRE(riskEventJson1["sectorId"].toInt() == 2);
    REQUIRE(riskEventJson1["acknowledged"].toBool() == false);
    REQUIRE(riskEventJson1["riskSeverity"].toString() == "NORMAL");
    REQUIRE(riskEventJson1["createdTimestamp"].toString() == "2024-06-01T12:00:00.000Z");
    REQUIRE(riskEventJson1["acknowledgedTimestamp"].toString() == "2024-06-01T12:05:00.000Z");
    REQUIRE(riskEventJson1["message"].toString() == "Test risk event");

    const auto mergedRiskEventJson = riskEventDataJson["mergedRiskEvents"].toArray()[0].toObject();
    REQUIRE(mergedRiskEventJson["sectorId"].toInt() == 2);
    qDebug() << mergedRiskEventJson["summaryMessage"].toString();
    REQUIRE(mergedRiskEventJson["summaryMessage"].toString() == "Risk severity in sector 2 changed from AT_RISK to CONGESTED");
    REQUIRE(mergedRiskEventJson["lastMessage"].toString() == "Test risk event 3");

    const auto sectorSummaryDataJson = json["sectorSummaryData"].toObject();
    REQUIRE(sectorSummaryDataJson["rowsCount"].toInt() == 2);
    REQUIRE(sectorSummaryDataJson["columnsCount"].toInt() == 2);
    REQUIRE(sectorSummaryDataJson["minLongitude"].toDouble() == -180.0);
    REQUIRE(sectorSummaryDataJson["maxLongitude"].toDouble() == 180.0);
    REQUIRE(sectorSummaryDataJson["minLatitude"].toDouble() == -90.0);
    REQUIRE(sectorSummaryDataJson["maxLatitude"].toDouble() == 90.0);
    REQUIRE(sectorSummaryDataJson["sectorSummaries"].toArray().size() == 4);

    const auto sectorSummaryJson1 = sectorSummaryDataJson["sectorSummaries"].toArray()[0].toObject();
    REQUIRE(sectorSummaryJson1["sectorId"].toInt() == 0);
    REQUIRE(sectorSummaryJson1["row"].toInt() == 0);
    REQUIRE(sectorSummaryJson1["column"].toInt() == 0);
    REQUIRE(sectorSummaryJson1["localAircraftCount"].toInt() == 0);
    REQUIRE(sectorSummaryJson1["localAircraftBaseCapacity"].toInt() == 10);
    REQUIRE(sectorSummaryJson1["localAircraftEffectiveCapacity"].toInt() == 8);
    REQUIRE(sectorSummaryJson1["weatherSeverity"].toString() == "NORMAL");
    REQUIRE(sectorSummaryJson1["riskSeverity"].toString() == "NORMAL");

    const auto trackDataJson = json["trackData"].toObject();
    REQUIRE(trackDataJson["totalAircraftCount"].toInt() == 1);
    REQUIRE(trackDataJson["coordinateSystem"].toString() == "WGS84");
    REQUIRE(trackDataJson["tracks"].toArray().size() == 1);

    const auto trackJson = trackDataJson["tracks"].toArray()[0].toObject();
    REQUIRE(trackJson["icao24"].toString() == "ABCD1234");
    REQUIRE(trackJson["timestamp"].toString() == "2024-06-01T12:00:00.000Z");
    REQUIRE(trackJson["position"].toObject()["latitudeDegrees"].toDouble() == 40.7128);
    REQUIRE(trackJson["position"].toObject()["longitudeDegrees"].toDouble() == -74.0060);
    REQUIRE(trackJson["position"].toObject()["altitudeFeet"].toInt() == 30000);
    REQUIRE(trackJson["velocity"].toObject()["groundSpeedKnots"].toInt() == 450);
    REQUIRE(trackJson["velocity"].toObject()["verticalSpeedFeetPerMinute"].toInt()  == 0);
    REQUIRE(trackJson["headingDegrees"].toInt() == 90);
    REQUIRE(trackJson["groundTrackDegrees"].toInt() == 90);
}