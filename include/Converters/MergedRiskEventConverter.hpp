#pragma once

#include <vector>

#include "Proto/FlightData.hpp"

class MergedRiskEvent;
class QJsonArray;
class QJsonObject;

class MergedRiskEventConverter
{
public:
    static toJson(const MergedRiskEvent& mergedRiskEvent);
    static toJson(const std::vector<MergedRiskEvent>& mergedRiskEvents);

    MergedRiskEventConverter() = delete;
};