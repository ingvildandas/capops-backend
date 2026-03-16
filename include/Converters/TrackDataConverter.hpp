#pragma once

#include <vector>

#include "Proto/FlightData.hpp"

class TrackData;
class TrackDataProto;
class QJsonObject;

class TrackDataConverter
{
public:
    static TrackData fromJson(const QJsonObject& json);
    static QJsonObject toJson(const TrackData& trackData);
    static TrackData fromProto(const TrackDataProto& protoTrackData);

    TrackDataConverter() = delete;
};