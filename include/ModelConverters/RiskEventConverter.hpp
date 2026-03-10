#pragma once

class RiskEvent;
class QJsonObject;

class RiskEventConverter
{
public:
    static RiskEvent fromJson(const QJsonObject& json);
    static QJsonObject toJson(const RiskEvent& riskEvent);
};
