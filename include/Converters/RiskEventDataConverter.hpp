#include <vector>

#include "Proto/FlightData.hpp"

class RiskEventData;
class RiskEventDataProto;
class QJsonObject;

class RiskEventDataConverter
{
public:
    static RiskEventData fromJson(const QJsonObject& json);
    static QJsonObject toJson(const RiskEventData& riskEventData);
    static RiskEventData fromProto
    (
        const RiskEventDataProto& protoRiskEventData
    );

    RiskEventDataConverter() = delete;
};