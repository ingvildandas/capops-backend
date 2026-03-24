#include <vector>

#include <QJsonArray>
#include <QJsonObject>
#include <QVector>

#include "Converters/MergedRiskEventConverter.hpp"
#include "Models/MergedRiskEvent.hpp"
#include "Models/RiskEvent.hpp"

MergedRiskEvent MergedRiskEventConverter::fromJson(const QJsonObject& json)
{
    int sectorId = json["sectorId"].toInt();
    QString summaryMessage = json["summaryMessage"].toString();
    QString lastMessage = json["lastMessage"].toString();
    QString checksum = json["checksum"].toString();

    std::vector<RiskEvent> riskEvents;
    QJsonArray riskEventIds = json["riskEventIds"].toArray();
    for (const auto& riskEventId : riskEventIds)
    {
        // Create RiskEvent objects with only the ID set, as we don't have the full data here.
        riskEvents.emplace_back(riskEventId.toInt(), sectorId, false, "", QDateTime(), QDateTime(), "");
    }

    MergedRiskEvent mergedRiskEvent(sectorId, riskEvents, checksum);

    return mergedRiskEvent;
}

QJsonObject MergedRiskEventConverter::toJson
(
    const MergedRiskEvent& mergedRiskEvent
)
{
    std::vector<RiskEvent> riskEvents = mergedRiskEvent.getRiskEvents();
    QString checksum = mergedRiskEvent.getChecksum();
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
        { "riskEventIds", riskEventIds },
        { "checksum", checksum }
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
