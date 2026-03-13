#include <string>
#include <vector>

#include <QJsonArray>
#include <QJsonObject>

#include "Converters/RiskEventConverter.hpp"
#include "Models/RiskEvent.hpp"

RiskEvent RiskEventConverter::fromJson(const QJsonObject& json)
{
    int riskEventId = json["riskEventId"].toInt();
    int riskSeverity = json["riskSeverity"].toInt();
    std::string message = json["message"].toString().toStdString();
    bool acknowledged = json["acknowledged"].toBool();

    return RiskEvent(riskEventId, riskSeverity, message, acknowledged);
}

std::vector<RiskEvent> RiskEventConverter::fromJson(const QJsonArray& jsonArray)
{
    std::vector<RiskEvent> riskEvents;
    riskEvents.reserve(jsonArray.size());

    for (const auto& value : jsonArray)
    {
        QJsonObject obj = value.toObject();
        riskEvents.push_back(fromJson(obj));
    }

    return riskEvents;
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

RiskEvent RiskEventConverter::fromProto(const RiskEventProto& protoRiskEvent)
{
    int riskEventId = t.riskeventid(); 
    int riskSeverity = t.risseverity();
    QString message = t.message();
    bool acknowledged = t.acknowledged();
    
    return RiskEvent(
        riskEventId,
        riskSeverity,
        message,
        acknowledged                
    )
}

std::vector<RiskEvent> RiskEventConverter::fromProto
(
    const google::protobuf::RepeatedPtrField<RiskEventProto>& protoRiskEvents
)
{
    std::vector<RiskEvent> riskEvents;
    riskEvents.reserve(protoRiskEvents.size());

    for (const auto& t : protoRiskEvent)
    {
        riskEvents.push_back(fromProto(t));
    }
}