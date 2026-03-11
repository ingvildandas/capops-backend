#pragma once

#include <vector>

class RiskEvent;
class QJsonArray;
class QJsonObject;

class RiskEventConverter
{
public:
    static RiskEvent fromJson(const QJsonObject& json);
    static std::vector<RiskEvent> fromJson(const QJsonArray& jsonArray);
    static QJsonObject toJson(const RiskEvent& riskEvent);
    static QJsonArray toJson(const std::vector<RiskEvent>& riskEvents);
};
