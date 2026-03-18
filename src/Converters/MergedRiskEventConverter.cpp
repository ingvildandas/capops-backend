#include <vector>

#include <QJsonArray>
#include <QJsonObject>
#include <QVector>

#include "Converters/MergedRiskEventConverter.hpp"
#include "MergedRiskEvent.hpp"

QJsonObject MergedRiskEventConverter::toJson
(
    const MergedRiskEvent& mergedRiskEvent
)
{
    std::vector<RiskEvent> riskEvents = mergedRiskEvent.getRiskEvents();
    QVector<int> riskEventIds;
    for (const auto& riskEvent : riskEvents)    {
        riskEventIds.append(riskEvent.getId());
    }

    QJsonObject json;
    json["id"] = QString::fromStdString(mergedRiskEvent.id);
    json["description"] = QString::fromStdString(mergedRiskEvent.description);
    json["severity"] = mergedRiskEvent.severity;
    json["riskEventIds"] = QJsonArray::fromVector(riskEventIds);
    return json;
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
