#pragma once

#include <vector>

#include "Proto/FlightData.hpp"

class RiskEvent;
class QJsonArray;
class QJsonObject;

class RiskEventConverter
{
public:
    RiskEventConverter() = delete;

    static RiskEvent fromJson(const QJsonObject& json);
    static std::vector<RiskEvent> fromJson(const QJsonArray& jsonArray);
    static QJsonObject toJson(const RiskEvent& riskEvent);
    static QJsonArray toJson(const std::vector<RiskEvent>& riskEvents);
    static RiskEvent fromProto(const RiskEventProto& protoRiskEvent);
    static std::vector<RiskEvent> fromProto
    (
        const google::protobuf::RepeatedPtrField<RiskEventProto>& protoRiskEvents
    );
};
