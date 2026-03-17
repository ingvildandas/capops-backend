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
    int rowsCount = json["rowsCount"].toInt();
    int columnsCount = json["columnsCount"].toInt();
    double minLongitude = json["minLongitude"].toDouble();
    double maxLongitude = json["maxLongitude"].toDouble();
    double minLatitude = json["minLatitude"].toDouble();
    double maxLatitude = json["maxLatitude"].toDouble();
    std::vector<SectorSummary> sectorSummaries = 
        SectorSummaryConverter::fromJson(json["sectorSummaries"].toArray());

    return SectorSummaryData
    (
        rowsCount, 
        columnsCount, 
        minLongitude, 
        maxLongitude, 
        minLatitude, 
        maxLatitude, 
        sectorSummaries
    );
}

QJsonObject SectorSummaryDataConverter::toJson
(
    const SectorSummaryData& sectorSummaryData
)
{
    return QJsonObject
    {
        { "rowsCount", sectorSummaryData.getRowsCount() },
        { "columnsCount", sectorSummaryData.getColumnsCount() },
        { "minLongitude", sectorSummaryData.getMinLongitude() },
        { "maxLongitude", sectorSummaryData.getMaxLongitude() },
        { "minLatitude", sectorSummaryData.getMinLatitude() },
        { "maxLatitude", sectorSummaryData.getMaxLatitude() },
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
    int rowsCount = protoSectorSummary.rowscount();
    int columnsCount = protoSectorSummary.columnscount();
    double minLongitude = protoSectorSummary.minlongitude();
    double maxLongitude = protoSectorSummary.maxlongitude();
    double minLatitude = protoSectorSummary.minlatitude();
    double maxLatitude = protoSectorSummary.maxlatitude();
    std::vector<SectorSummary> sectorSummaries = 
        SectorSummaryConverter::fromProto(protoSectorSummary.sectorsummaries());

    return SectorSummaryData
    (
        rowsCount, 
        columnsCount, 
        minLongitude, 
        maxLongitude, 
        minLatitude, 
        maxLatitude, 
        sectorSummaries
    );
}