#pragma once

class EnvironmentManager;
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
        const EnvironmentManager& envManager
    );
    static FlightData fromProto(const FlightDataProto& proto);
};