#include <string>
#include <vector>

#include <QJsonArray>
#include <QJsonObject>

#include "ModelConverters/RiskEventConverter.hpp"
#include "Models/RiskEvent.hpp"

RiskEvent RiskEventConverter::fromJson(const QJsonObject& json)
{
    int riskEventId = json["riskEventId"].toInt();
    int riskSeverity = json["riskSeverity"].toInt();
    std::string message = json["message"].toString().toStdString();
    bool acknowledged = json["acknowledged"].toBool();

    return RiskEvent(riskEventId, riskSeverity, message, acknowledged);
}

QJsonObject RiskEventConverter::toJson(const RiskEvent& riskEvent)
{
    return 
    {
        { "riskEventId", riskEvent.getRiskEventId() },
        { "riskSeverity", riskEvent.getRiskSeverity() },
        { "message", QString::fromStdString(riskEvent.getMessage()) },
        { "acknowledged", riskEvent.getAcknowledged() }
    };
}

QJsonArray RiskEventConverter::toJson(const std::vector<RiskEvent>& riskEvents)
{
    QJsonArray riskEventArray;
    for (RiskEvent riskEvent : riskEvents)
    {
        riskEventArray.append(toJson(riskEvent));
    }

    return riskEventArray;
}