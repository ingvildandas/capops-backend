#include <string>
#include <vector>

#include <QJsonArray>
#include <QJsonObject>

#include "Converters/TrackConverter.hpp"
#include "Models/Track.hpp"
#include "Proto/FlightData.hpp"
#include "Structs/TrackStructs.hpp"

Track TrackConverter::fromJson(const QJsonObject& json)
{
    QString icao24 = json["icao24"].toString();
    QDateTime timestamp = QDateTime::fromString(json["timestamp"].toString());
    TrackPosition position = positionFromJson(json["position"].toObject());
    TrackVelocity velocity = velocityFromJson(json["velocity"].toObject());
    double headingDegrees = json["headingDegrees"].toDouble(); 
    double groundTrackDegrees = json["groundTrackDegrees"].toDouble();

    return Track
    (
        icao24,
        timestamp,
        position,
        velocity,
        headingDegrees,
        groundTrackDegrees
    );
}

std::vector<Track> TrackConverter::fromJson(const QJsonArray& jsonArray)
{
    std::vector<Track> tracks;
    tracks.reserve(jsonArray.size());

    for (const auto& value : jsonArray)
    {
        QJsonObject obj = value.toObject();
        tracks.push_back(fromJson(obj));
    }

    return tracks;
}

QJsonObject TrackConverter::toJson(const Track& track)
{
    return
    {
        { "icao24", track.getIcao24() },
        { "timestamp", track.getTimestamp().toString() },
        { "Position", positionToJson(track.getPosition()) },
        { "Velocity", velocityToJson(track.getVelocity()) },
        { "headingDegrees", track.getHeadingDegrees() },
        { "groundTrackDegrees", track.getGroundTrackDegrees() }
    };
}

QJsonArray TrackConverter::toJson(const std::vector<Track>& tracks)
{
    QJsonArray trackArray;
    for (Track track : tracks)
    {
        trackArray.append(toJson(track));
    }

    return trackArray;
}

TrackPosition TrackConverter::positionFromJson(const QJsonObject& json)
{
    double latitudeDegrees = json["latitudeDegrees"].toDouble();
    double longitudeDegrees = json["longitudeDegrees"].toDouble();
    double altitudeMeters = json["altitudeMeters"].toDouble();

    return TrackPosition
    {
        latitudeDegrees, 
        longitudeDegrees, 
        altitudeMeters
    };
}

TrackVelocity TrackConverter::velocityFromJson(const QJsonObject& json)
{
    double groundSpeedKnots = 
        json["groundSpeedKnots"].toDouble();
    double verticalSpeedFeetPerMinute = 
        json["verticalSpeedFeetPerMinute"].toDouble();

    return TrackVelocity
    {
        groundSpeedKnots, 
        verticalSpeedFeetPerMinute
    };
}

QJsonObject TrackConverter::positionToJson(const TrackPosition& position)
{
    return
    {
        { "latitudeDegrees", position.latitudeDegrees },
        { "longitudeDegrees", position.longitudeDegrees },
        { "altitudeMeters", position.altitudeMeters }
    };
}

QJsonObject TrackConverter::velocityToJson(const TrackVelocity& velocity)
{
    return
    {
        { "groundSpeedKnots", velocity.groundSpeedKnots },
        { "verticalSpeedFeetPerMinute", velocity.verticalSpeedFeetPerMinute }
    };
}

Track TrackConverter::fromProto(const TrackProto& protoTrack)
{
    QString icao24 = QString::fromStdString(protoTrack.icao24());
    QDateTime timestamp = 
        QDateTime::fromString(QString::fromStdString(protoTrack.timestamp()));

    TrackPosition position = positionFromProto(protoTrack.position());
    TrackVelocity velocity = velocityFromProto(protoTrack.velocity());
    double headingDegrees = protoTrack.headingdegrees();
    double groundTrackDegrees = protoTrack.groundtrackdegrees();

    return Track
    (
        icao24, 
        timestamp, 
        position, 
        velocity, 
        headingDegrees,
        groundTrackDegrees
    );
}

std::vector<Track> TrackConverter::fromProto
(
    const google::protobuf::RepeatedPtrField<TrackProto>& protoTracks
)
{
    std::vector<Track> tracks;
    tracks.reserve(protoTracks.size());

    for (const auto& t : protoTracks)
    {
        tracks.push_back(fromProto(t));
    }

    return tracks;
}

TrackPosition TrackConverter::positionFromProto
(
    const PositionProto& Position
)
{
    QString frame = QString::fromStdString(Position.frame());
    double latitudeDegrees = Position.latitudedegrees();
    double longitudeDegrees = Position.longitudedegrees();
    double altitudeMeters = Position.altitudemeters();

    return TrackPosition
    {
        latitudeDegrees, 
        longitudeDegrees, 
        altitudeMeters
    };
}

TrackVelocity TrackConverter::velocityFromProto
(
    const VelocityProto& Velocity
)
{
    double groundSpeedKnots = Velocity.groundSpeedKnots();
    double verticalSpeedFeetPerMinute = Velocity.verticalSpeedFeetPerMinute();
    
    return TrackVelocity
    {
        groundSpeedKnots,
        verticalSpeedFeetPerMinute,
    };
}