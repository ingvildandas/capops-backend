#include <QJsonArray>
#include <QJsonObject>

#include "Converters/FlightDataDtoConverter.hpp"
#include "Converters/MetadataConverter.hpp"
#include "Converters/RiskEventDataConverter.hpp"
#include "Converters/SectorSummaryDataConverter.hpp"
#include "Converters/TrackDataConverter.hpp"
#include "Dtos/FlightDataDto.hpp"
#include "Models/Metadata.hpp"
#include "Models/RiskEventData.hpp"
#include "Models/SectorSummaryData.hpp"
#include "Models/TrackData.hpp"

FlightDataDto FlightDataDtoConverter::fromJson(const QJsonObject& json)
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

    return FlightDataDto(metadata, riskEventData, sectorSummaryData, trackData);
}

QJsonObject FlightDataDtoConverter::toJson(const FlightDataDto& dto)
{
    return
    {
        { "metadata", MetadataConverter::toJson(dto.getMetadata()) },
        { "riskEventData", RiskEventDataConverter::toJson(dto.getRiskEventData()) },
        { "sectorSummaryData", SectorSummaryDataConverter::toJson(dto.getSectorSummaryData()) },
        { "trackData", TrackDataConverter::toJson(dto.getTrackData()) }
    };
}