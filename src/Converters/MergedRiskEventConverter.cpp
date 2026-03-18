#include <vector>

#include <QJsonArray>
#include <QJsonObject>
#include <QVector>

#include "Converters/MergedRiskEventConverter.hpp"
#include "Models/MergedRiskEvent.hpp"
#include "Models/RiskEvent.hpp"

QJsonObject MergedRiskEventConverter::toJson
(
    const MergedRiskEvent& mergedRiskEvent
)
{
    std::vector<RiskEvent> riskEvents = mergedRiskEvent.getRiskEvents();
    QJsonArray riskEventIds;
    for (const auto& riskEvent : riskEvents)
    {
        riskEventIds.append(riskEvent.getRiskEventId());
    }

    return QJsonObject
    {
        { "sectorId", mergedRiskEvent.getSectorId() },
        { "summaryMessage", mergedRiskEvent.getSummaryMessage() },
        { "lastMessage", mergedRiskEvent.getLastMessage() },
        { "riskEventIds", riskEventIds }
    };
}

QJsonArray MergedRiskEventConverter::toJson
(
    const std::vector<MergedRiskEvent>& mergedRiskEvents
)
{
    QJsonArray jsonArray;
    for (const auto& mergedRiskEvent : mergedRiskEvents)
    {
        jsonArray.append(toJson(mergedRiskEvent));
    }
    return jsonArray;
}
