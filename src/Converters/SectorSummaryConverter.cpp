#include <string>
#include <vector>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QStringList>
#include <QVector>

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
    QJsonArray icao24ListJson = json["icao24List"].toArray();

    QVector<QString> icao24List;
    icao24List.reserve(icao24ListJson.size());
    
    for (const QJsonValue &value : icao24ListJson) {
        icao24List.append(value.toString());
    }
    
    return SectorSummary
    (
        sectorId,
        row,
        colunmn,
        localAircraftCount,
        localAircraftBaseCapacity,
        localAircraftEffectiveCapacity,
        weatherSeverity,
        riskSeverity,
        icao24List
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
    
    QVector<QString> icao24List = sectorSummary.getIcao24List();
    QJsonArray icao24ListJson;
    for (const auto& icao24 : icao24List)
    {
        icao24ListJson.append(icao24);
    }
    return 
    {
        { "sectorId", sectorSummary.getSectorId() },
        { "row", sectorSummary.getRow() },
        { "column", sectorSummary.getColumn() },
        { "localAircraftCount", sectorSummary.getLocalAircraftCount() },
        { "localAircraftBaseCapacity", sectorSummary.getLocalAircraftBaseCapacity() },
        { 
            "localAircraftEffectiveCapacity", 
            sectorSummary.getLocalAircraftEffectiveCapacity() 
        },
        { "weatherSeverity", sectorSummary.getWeatherSeverity() },
        { "riskSeverity", sectorSummary.getRiskSeverity() },
        { "icao24List", icao24ListJson }
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
    QVector<QString> icao24List;

    for (std::string icao24 : protoSectorSummary.icao24list())
    {
        icao24List.push_back(QString::fromStdString(icao24));
    }

    return SectorSummary
    (
        sectorId,
        row,
        colunmn,
        localAircraftCount,
        localAircraftBaseCapacity,
        localAircraftEffectiveCapacity,
        weatherSeverity,
        riskSeverity,
        icao24List
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