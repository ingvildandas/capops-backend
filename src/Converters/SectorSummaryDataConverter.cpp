#include <vector>

#include <QJsonArray>
#include <QJsonObject>
#include <QString>

#include "Converters/SectorSummaryDataConverter.hpp"
#include "Converters/SectorSummaryConverter.hpp"
#include "Models/SectorSummary.hpp"
#include "Models/SectorSummaryData.hpp"
#include "Proto/FlightData.hpp"

SectorSummaryData SectorSummaryDataConverter::fromJson(const QJsonObject& json)
{
    int totalAircraftCount = json["totalAircraftCount"].toInt();
    std::vector<SectorSummary> sectorSummaries = 
        SectorSummaryConverter::fromJson(json["sectorSummaries"].toArray());

    return SectorSummaryData(totalAircraftCount, sectorSummaries);
}

QJsonObject SectorSummaryDataConverter::toJson
(
    const SectorSummaryData& sectorSummaryData
)
{
    return QJsonObject
    {
        { "totalAircraftCount", sectorSummaryData.getTotalAircraftCount() },
        { 
            "sectorSummaries", 
            SectorSummaryConverter::toJson(sectorSummaryData.getSectorSummaries()) 
        }
    };
}

SectorSummaryData SectorSummaryDataConverter::fromProto
(
    const SectorSummaryDataProto& protoSectorSummary
)
{
    int totalAircraftCount = protoSectorSummary.totalaircraftcount();
    std::vector<SectorSummary> sectorSummaries = 
        SectorSummaryConverter::fromProto(protoSectorSummary.sectorsummaries());

    return SectorSummaryData(totalAircraftCount, sectorSummaries);
}