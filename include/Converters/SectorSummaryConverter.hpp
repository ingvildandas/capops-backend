#pragma once

#include <vector>

class SectorSummary;
class QJsonArray;
class QJsonObject;

class SectorSummaryConverter
{
public:
    static SectorSummary fromJson(const QJsonObject& json);
    static std::vector<SectorSummary> fromJson(const QJsonArray& jsonArray);
    static QJsonObject toJson(const SectorSummary& sectorSummary);
    static QJsonArray toJson(const std::vector<SectorSummary>& sectorSummaries);
};