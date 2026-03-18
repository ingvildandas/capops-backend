#include <QJsonArray>
#include <QJsonObject>

#include "Converters/FlightDataConverter.hpp"
#include "Converters/MetadataConverter.hpp"
#include "Converters/RiskEventDataConverter.hpp"
#include "Converters/SectorSummaryDataConverter.hpp"
#include "Converters/TrackDataConverter.hpp"
#include "Models/FlightData.hpp"
#include "Models/Metadata.hpp"
#include "Models/RiskEventData.hpp"
#include "Models/SectorSummaryData.hpp"
#include "Models/TrackData.hpp"

FlightData FlightDataConverter::fromJson(const QJsonObject& json)
{
    QJsonObject metadataObj = json["metadata"].toObject();
    QJsonObject riskEventDataObj = json["riskEventData"].toObject();
    QJsonObject sectorSummaryDataObj = json["sectorSummaryData"].toObject();
    QJsonObject trackDataObj = json["trackData"].toObject();

    Metadata metadata = MetadataConverter::fromJson(metadataObj);
    RiskEventData riskEventData = 
        RiskEventDataConverter::fromJson(riskEventDataObj);
    SectorSummaryData sectorSummaryData = 
        SectorSummaryDataConverter::fromJson(sectorSummaryDataObj);
    TrackData trackData = TrackDataConverter::fromJson(trackDataObj);

    return FlightData(metadata, riskEventData, sectorSummaryData, trackData);
}

QJsonObject FlightDataConverter::toJson
(
    const FlightData& flightData,
    const EnvironmentManager& envManager
)
{
    return
    {
        { 
            "metadata", 
            MetadataConverter::toJson(flightData.getMetadata(), envManager)
        },
        { 
            "riskEventData", 
            RiskEventDataConverter::toJson(flightData.getRiskEventData()) 
        },
        { 
            "sectorSummaryData", 
            SectorSummaryDataConverter::toJson(flightData.getSectorSummaryData()) 
        },
        { "trackData", TrackDataConverter::toJson(flightData.getTrackData()) }
    };
}

FlightData FlightDataConverter::fromProto(const FlightDataProto& proto)
{
    Metadata metadata = MetadataConverter::fromProto(proto.metadata());

    TrackData trackData = 
        TrackDataConverter::fromProto(proto.trackdata());
    SectorSummaryData sectorSummaryData = 
        SectorSummaryDataConverter::fromProto(proto.sectorsummarydata());
    RiskEventData riskEventData = 
        RiskEventDataConverter::fromProto(proto.riskeventdata());

    return FlightData(metadata, riskEventData, sectorSummaryData, trackData);
}