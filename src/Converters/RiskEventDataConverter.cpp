#include <vector>

#include <QJsonArray>
#include <QJsonObject>
#include <QString>

#include "Converters/RiskEventDataConverter.hpp"
#include "Converters/MergedRiskEventConverter.hpp"
#include "Converters/RiskEventConverter.hpp"
#include "Models/MergedRiskEvent.hpp"
#include "Models/RiskEvent.hpp"
#include "Models/RiskEventData.hpp"
#include "Proto/FlightData.hpp"

RiskEventData RiskEventDataConverter::fromJson(const QJsonObject& json)
{
    int totalRiskEventCount = json["riskEventCount"].toInt();
    std::vector<RiskEvent> riskEvents = 
        RiskEventConverter::fromJson(json["riskEvents"].toArray());

    return RiskEventData(totalRiskEventCount, riskEvents);
}

QJsonObject RiskEventDataConverter::toJson
(
    const RiskEventData& riskEventData
)
{
    return QJsonObject
    {
        { "riskEventCount", riskEventData.getRiskEventCount() },
        { 
            "riskEvents", 
            RiskEventConverter::toJson(riskEventData.getRiskEvents()) 
        },
        {
            "mergedRiskEvents",
            MergedRiskEventConverter::toJson(riskEventData.getMergedRiskEvents())
        }
    };
}

RiskEventData RiskEventDataConverter::fromProto
(
    const RiskEventDataProto& protoRiskEventData
)
{
    int totalRiskEventCount = protoRiskEventData.riskeventcount();
    std::vector<RiskEvent> riskEvents = 
        RiskEventConverter::fromProto(protoRiskEventData.riskevents());

    return RiskEventData(totalRiskEventCount, riskEvents);
}