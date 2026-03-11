#pragma once

class FlightDataDto;
class QJsonObject;

class FlightDataDtoConverter
{
public:
    static FlightDataDto fromJson(const QJsonObject& json);
    static QJsonObject toJson(const FlightDataDto& dto);
};