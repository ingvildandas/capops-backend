#include <string>
#include <vector>

#include <QJsonArray>
#include <QJsonObject>
#include <QString>

#include "Converters/RiskEventConverter.hpp"
#include "Models/RiskEvent.hpp"

RiskEvent RiskEventConverter::fromJson(const QJsonObject& json)
{
    int riskEventId = json["riskEventId"].toInt();
    int sectorId = json["sectorId"].toInt();
    bool acknowledged = json["acknowledged"].toBool();
    QString riskSeverity = json["riskSeverity"].toString();
    QDateTime createdTimestamp = 
        QDateTime::fromString(json["createdTimestamp"].toString(), Qt::ISODate);
    QDateTime acknowledgedTimestamp = 
        QDateTime::fromString(json["acknowledgedTimestamp"].toString(), Qt::ISODate);
    QString message = json["message"].toString();

    return RiskEvent
    (
        riskEventId, 
        sectorId, 
        acknowledged, 
        riskSeverity,
        createdTimestamp, 
        acknowledgedTimestamp, 
        message
    );
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
        { "sectorId", riskEvent.getSectorId() },
        { "acknowledged", riskEvent.getAcknowledged() },
        { "riskSeverity", riskEvent.getRiskSeverity() },
        { "createdTimestamp", riskEvent.getCreatedTimestamp().toString(Qt::ISODateWithMs) },
        { "acknowledgedTimestamp", riskEvent.getAcknowledgedTimestamp().toString(Qt::ISODateWithMs) },
        { "message", riskEvent.getMessage() }
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
    int riskEventId = protoRiskEvent.riskeventid(); 
    int sectorId = protoRiskEvent.sectorid();
    bool acknowledged = protoRiskEvent.acknowledged();
    QString riskSeverity = QString::fromStdString(protoRiskEvent.riskseverity());
    QDateTime createdTimestamp = 
        QDateTime::fromString(QString::fromStdString(protoRiskEvent.createdtimestamp()), Qt::ISODate);
    QDateTime acknowledgedTimestamp = 
        QDateTime::fromString(QString::fromStdString(protoRiskEvent.acknowledgedtimestamp()), Qt::ISODate);
    QString message = QString::fromStdString(protoRiskEvent.message());
    
    return RiskEvent(
        riskEventId,
        sectorId,
        acknowledged,
        riskSeverity,
        createdTimestamp,
        acknowledgedTimestamp,
        message               
    );
}

std::vector<RiskEvent> RiskEventConverter::fromProto
(
    const google::protobuf::RepeatedPtrField<RiskEventProto>& protoRiskEvents
)
{
    std::vector<RiskEvent> riskEvents;
    riskEvents.reserve(protoRiskEvents.size());

    for (const auto& t : protoRiskEvents)
    {
        riskEvents.push_back(fromProto(t));
    }

    return riskEvents;
}