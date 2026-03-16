#pragma once

#include <vector>

#include "Proto/FlightData.hpp"

class SectorSummary;
class SectorSummaryData;
class SectorSummaryDataProto;
class QJsonObject;

class SectorSummaryDataConverter
{
public:
    static SectorSummaryData fromJson(const QJsonObject& json);
    static QJsonObject toJson(const SectorSummaryData& sectorSummaryData);
    static SectorSummaryData fromProto
    (
        const SectorSummaryDataProto& protoSectorSummary
    );

    SectorSummaryDataConverter() = delete;
};