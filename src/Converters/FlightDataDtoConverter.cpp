#include <QJsonArray>
#include <QJsonObject>

#include "Converters/FlightDataDtoConverter.hpp"
#include "Converters/MetadataConverter.hpp"
#include "Converters/RiskEventConverter.hpp"
#include "Converters/SectorSummaryConverter.hpp"
#include "Converters/TrackConverter.hpp"
#include "Dtos/FlightDataDto.hpp"
#include "Models/RiskEvent.hpp"
#include "Models/SectorSummary.hpp"
#include "Models/Track.hpp"

FlightDataDto FlightDataDtoConverter::fromJson(const QJsonObject& json)
{
    QJsonObject metadataObj = json["metadata"].toObject();
    QJsonArray riskEventArray = json["riskEvents"].toArray();
    QJsonArray sectorSummaryArray = json["sectorSummaries"].toArray();
    QJsonArray trackArray = json["tracks"].toArray();

    Metadata metadata = MetadataConverter::fromJson(metadataObj);
    std::vector<RiskEvent> riskEvents = 
        RiskEventConverter::fromJson(riskEventArray);
    std::vector<SectorSummary> sectorSummaries = 
        SectorSummaryConverter::fromJson(sectorSummaryArray);
    std::vector<Track> tracks = TrackConverter::fromJson(trackArray);

    return FlightDataDto(metadata, riskEvents, sectorSummaries, tracks);
}

QJsonObject FlightDataDtoConverter::toJson(const FlightDataDto& dto)
{
    return
    {
        { "metadata", MetadataConverter::toJson(dto.getMetadata()) },
        { "riskEvents", RiskEventConverter::toJson(dto.getRiskEvents()) },
        { "sectorSummaries", SectorSummaryConverter::toJson(dto.getSectorSummaries()) },
        { "tracks", TrackConverter::toJson(dto.getTracks()) }
    };
}