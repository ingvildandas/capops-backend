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
    int localAircraftCount = json["localAircraftCount"].toInt();
    int localAircraftBaseCapacity = json["localAircraftBaseCapacity"].toInt();
    int localAircraftEffectiveCapacity = 
        json["localAircraftEffectiveCapacity"].toInt();
    QString weatherSeverity = json["weatherSeverity"].toString();
    QString riskSeverity = json["riskSeverity"].toString();
    
    return SectorSummary
    (
        sectorId,
        row,
        colunmn,
        localAircraftCount,
        localAircraftBaseCapacity,
        localAircraftEffectiveCapacity,
        weatherSeverity,
        riskSeverity
    );
}

std::vector<SectorSummary> SectorSummaryConverter::fromJson
(
    const QJsonArray& jsonArray
)
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
        { "localAircraftCount", sectorSummary.getLocalAircraftCount() },
        { "localAircraftBaseCapacity", sectorSummary.getLocalAircraftBaseCapacity() },
        { 
            "localAircraftEffectiveCapacity", 
            sectorSummary.getLocalAircraftEffectiveCapacity() 
        },
        { "weatherSeverity", sectorSummary.getWeatherSeverity() },
        { "riskSeverity", sectorSummary.getRiskSeverity() }
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
    int colunmn = protoSectorSummary.column();
    int localAircraftCount = protoSectorSummary.localaircraftcount();
    int localAircraftBaseCapacity = 
        protoSectorSummary.localaircraftbasecapacity();
    int localAircraftEffectiveCapacity = 
        protoSectorSummary.localaircrafteffectivecapacity();
    QString weatherSeverity = 
        QString::fromStdString(protoSectorSummary.weatherseverity());
    QString riskSeverity = 
        QString::fromStdString(protoSectorSummary.riskseverity());

    return SectorSummary
    (
        sectorId,
        row,
        colunmn,
        localAircraftCount,
        localAircraftBaseCapacity,
        localAircraftEffectiveCapacity,
        weatherSeverity,
        riskSeverity
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