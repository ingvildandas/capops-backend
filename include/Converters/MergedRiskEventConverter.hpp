#pragma once

#include <vector>

class MergedRiskEvent;
class QJsonArray;
class QJsonObject;

class MergedRiskEventConverter
{
public:
    static MergedRiskEvent fromJson(const QJsonObject& json);
    static QJsonObject toJson(const MergedRiskEvent& mergedRiskEvent);
    static QJsonArray toJson
    (
        const std::vector<MergedRiskEvent>& mergedRiskEvents
    );

    MergedRiskEventConverter() = delete;
};