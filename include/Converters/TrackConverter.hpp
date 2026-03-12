#pragma once

#include <vector>

#include "Proto/FlightData.hpp"

class Track;
class QJsonArray;
class QJsonObject;

struct TrackGlobalPosition;
struct TrackLocalPosition;
struct TrackGlobalVelocity;
struct TrackLocalVelocity;

class TrackConverter
{
public:
    static Track fromJson(const QJsonObject& json);
    static std::vector<Track> fromJson(const QJsonArray& jsonArray);
    static QJsonObject toJson(const Track& track);
    static QJsonArray toJson(const std::vector<Track>& tracks);
    static std::vector<Track> fromProto
    (
        const google::protobuf::RepeatedPtrField<TrackProto>& protoTracks
    );

private:
    static TrackGlobalPosition globalPositionFromJson(const QJsonObject& json);
    static TrackLocalPosition localPositionFromJson(const QJsonObject& json);
    static TrackGlobalVelocity globalVelocityFromJson(const QJsonObject& json);
    static TrackLocalVelocity localVelocityFromJson(const QJsonObject& json);
    
    static QJsonObject globalPositionToJson(const TrackGlobalPosition& position);
    static QJsonObject localPositionToJson(const TrackLocalPosition& position);
    static QJsonObject globalVelocityToJson(const TrackGlobalVelocity& velocity);
    static QJsonObject localVelocityToJson(const TrackLocalVelocity& velocity);

    static TrackGlobalPosition globalPositionFromProto
    (
        const GlobalPositionProto& globalPosition
    );
    static TrackLocalPosition localPositionFromProto
    (
        const LocalPositionProto& localPosition
    );
    static TrackGlobalVelocity globalVelocityFromProto
    (
        const GlobalVelocityProto& localVelocity
    );
    static TrackLocalVelocity localVelocityFromProto
    (
        const LocalVelocityProto& localVelocity
    ); 
};