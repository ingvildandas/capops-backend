#pragma once

#include <vector>

#include "Proto/FlightData.hpp"

class SectorSummary;
class QJsonArray;
class QJsonObject;

class SectorSummaryConverter
{
public:
    SectorSummaryConverter() = delete;
    
    static SectorSummary fromJson(const QJsonObject& json);
    static std::vector<SectorSummary> fromJson(const QJsonArray& jsonArray);
    static QJsonObject toJson(const SectorSummary& sectorSummary);
    static QJsonArray toJson(const std::vector<SectorSummary>& sectorSummaries);
    static SectorSummary fromProto(const SectorSummaryProto& protoSectorSummary);
    static std::vector<SectorSummary> fromProto
    (
        const google::protobuf::RepeatedPtrField<SectorSummaryProto>& 
            protoSectorSummaries
    );
};