#pragma once

#include <vector>

class MergedRiskEvent;
class QJsonArray;
class QJsonObject;

class MergedRiskEventConverter
{
public:
    static QJsonObject toJson(const MergedRiskEvent& mergedRiskEvent);
    static QJsonArray toJson
    (
        const std::vector<MergedRiskEvent>& mergedRiskEvents
    );

    MergedRiskEventConverter() = delete;
};