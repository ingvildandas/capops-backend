#pragma once

#include <vector>

#include "Proto/FlightData.hpp"

class Track;
class QJsonArray;
class QJsonObject;

struct TrackPosition;
struct TrackVelocity;

class TrackConverter
{
public:
    static Track fromJson(const QJsonObject& json);
    static std::vector<Track> fromJson(const QJsonArray& jsonArray);
    static QJsonObject toJson(const Track& track);
    static QJsonArray toJson(const std::vector<Track>& tracks);
    static Track fromProto(const TrackProto& protoTrack);
    static std::vector<Track> fromProto
    (
        const google::protobuf::RepeatedPtrField<TrackProto>& protoTracks
    );
    
    TrackConverter() = delete;

private:
    static TrackPosition positionFromJson(const QJsonObject& json);
    static TrackVelocity velocityFromJson(const QJsonObject& json);
    
    static QJsonObject positionToJson(const TrackPosition& position);
    static QJsonObject velocityToJson(const TrackVelocity& velocity);

    static TrackPosition positionFromProto
    (
        const PositionProto& position
    );
    static TrackVelocity velocityFromProto
    (
        const VelocityProto& velocity
    );
};