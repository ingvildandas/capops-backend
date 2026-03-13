#include <string>
#include <vector>

#include <QJsonArray>
#include <QJsonObject>

#include "Converters/SectorSummaryConverter.hpp"
#include "Models/SectorSummary.hpp"


SectorSummary SectorSummaryConverter::fromJson(const QJsonObject& json)
{
    int sectorId = json["sectorId"].toInt();
    int row = json["row"].toInt();
    int colunmn = json["column"].toInt();
    int weatherSeverity = json["weatherSeverity"].toInt();
    double weatherFactor = json["double"].toDouble();
    int localAircraftCount = json["localAircraftCount"].toInt();
    int localAircraftBaseCapacity = json["localAircraftBaseCapacity"].toInt();
    int localAircraftEffectiveCapacity = 
        json["localAircraftEffectiveCapacity"].toInt();
    
    return SectorSummary
    (
        sectorId,
        row,
        colunmn,
        weatherSeverity,
        weatherFactor,
        localAircraftCount,
        localAircraftBaseCapacity,
        localAircraftEffectiveCapacity
    );
}

std::vector<SectorSummary> SectorSummaryConverter::fromJson(const QJsonArray& jsonArray)
{
    std::vector<SectorSummary> sectorSummaries;
    sectorSummaries.reserve(jsonArray.size());

    for (const auto& value : jsonArray)
    {
        QJsonObject obj = value.toObject();
        sectorSummaries.push_back(fromJson(obj));
    }

    return sectorSummaries;
}

QJsonObject SectorSummaryConverter::toJson(const SectorSummary& sectorSummary)
{
    return 
    {
        { "sectorId", sectorSummary.getSectorId() },
        { "row", sectorSummary.getRow() },
        { "colunmn", sectorSummary.getColunmn() },
        { "weatherSeverity", sectorSummary.getWeatherSeverity() },
        { "weatherFactor", sectorSummary.getWeatherFactor() },
        { "localAircraftCount", sectorSummary.getLocalAircraftCount() },
        { "localAircraftBaseCapacity", sectorSummary.getLocalAircraftBaseCapacity() },
        { 
            "localAircraftEffectiveCapacity", 
            sectorSummary.getLocalAircraftEffectiveCapacity() 
        }
    };
}

QJsonArray SectorSummaryConverter::toJson(const std::vector<SectorSummary>& sectorSummaries)
{
    QJsonArray sectorSummaryArray;
    for (SectorSummary sectorSummary : sectorSummaries)
    {
        sectorSummaryArray.append(toJson(sectorSummary));
    }

    return sectorSummaryArray;
}

SectorSummary SectorSummaryConverter::fromProto
(
    const SectorSummaryProto& protoSectorSummary
)
{
    int sectorId = protoSectorSummary.sectorid();
    int row = protoSectorSummary.row();
    int colunmn = protoSectorSummary.colunmn();
    int weatherSeverity = protoSectorSummary.weatherseverity();
    double weatherFactor = protoSectorSummary.weatherfactor();
    int localAircraftCount = protoSectorSummary.localaircraftcount();
    int localAircraftBaseCapacity = 
        protoSectorSummary.localaircraftbasecapacity();
    int localAircraftEffectiveCapacity = 
        protoSectorSummary.localaircrafteffectivecapacity();

    return SectorSummary
    (
        sectorId,
        row,
        colunmn,
        weatherSeverity,
        weatherFactor,
        localAircraftCount,
        localAircraftBaseCapacity,
        localAircraftEffectiveCapacity
    );
}

std::vector<SectorSummary> SectorSummaryConverter::fromProto
(
    const google::protobuf::RepeatedPtrField<SectorSummaryProto>& 
        protoSectorSummaries
)
{
    std::vector<SectorSummary> sectorSummaries;
    sectorSummaries.reserve(protoSectorSummaries.size());

    for (const auto& t : protoSectorSummaries)
    {
        sectorSummaries.push_back(fromProto(t));
    }

    return sectorSummaries;
}