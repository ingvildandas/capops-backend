#pragma once

class RiskEvent;
class QJsonArray;
class QJsonObject;

class RiskEventConverter
{
public:
    static RiskEvent fromJson(const QJsonObject& json);
    static QJsonObject toJson(const RiskEvent& riskEvent);
    static QJsonArray toJson(const std::vector<const RiskEvent>& riskEvents);
};
