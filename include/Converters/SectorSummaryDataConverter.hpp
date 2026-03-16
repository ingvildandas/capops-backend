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
    static SectorSummary fromJson(const QJsonObject& json);
    static QJsonObject toJson(const SectorSummaryData& sectorSummary);
    static SectorSummary fromProto
    (
        const SectorSummaryDataProto& protoSectorSummary
    );

    SectorSummaryDataConverter() = delete;
};