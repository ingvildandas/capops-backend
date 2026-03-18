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
    const FlightData& dto,
    const EnvironmentManager& envManager
)
{
    return
    {
        { "metadata", MetadataConverter::toJson(dto.getMetadata(), envManager) },
        { "riskEventData", RiskEventDataConverter::toJson(dto.getRiskEventData()) },
        { "sectorSummaryData", SectorSummaryDataConverter::toJson(dto.getSectorSummaryData()) },
        { "trackData", TrackDataConverter::toJson(dto.getTrackData()) }
    };
}