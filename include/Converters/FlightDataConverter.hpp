#pragma once

class IEnvironmentManager;
class FlightData;
class FlightDataProto;
class QJsonObject;

class FlightDataConverter
{
public:
    static FlightData fromJson(const QJsonObject& json);
    static QJsonObject toJson
    (
        const FlightData& dto,
        const IEnvironmentManager& envManager
    );
    static FlightData fromProto(const FlightDataProto& proto);
};