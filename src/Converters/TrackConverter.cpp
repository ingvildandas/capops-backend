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
    TrackGlobalPosition globalPosition = 
        globalPositionFromJson(json["globalPosition"].toObject());
    TrackLocalPosition localPosition = 
        localPositionFromJson(json["localPosition"].toObject());
    TrackGlobalVelocity globalVelocity = 
        globalVelocityFromJson(json["globalVelocity"].toObject());
    TrackLocalVelocity localVelocity = 
        localVelocityFromJson(json["localVelocity"].toObject());
    double headingDegrees = json["headingDegrees"].toDouble(); 

    return Track
    (
        icao24,
        timestamp,
        globalPosition,
        localPosition,
        globalVelocity,
        localVelocity,
        headingDegrees
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
        { "globalPosition", globalPositionToJson(track.getGlobalPosition()) },
        { "localPosition", localPositionToJson(track.getLocalPosition()) },
        { "globalVelocity", globalVelocityToJson(track.getGlobalVelocity()) },
        { "localVelocity", localVelocityToJson(track.getLocalVelocity()) },
        { "headingDegrees", track.getHeadingDegrees() }
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

TrackGlobalPosition TrackConverter::globalPositionFromJson(const QJsonObject& json)
{
    QString frame = json["frame"].toString();
    double latitudeDegrees = json["latitudeDegrees"].toDouble();
    double longitudeDegrees = json["longitudeDegrees"].toDouble();
    double altitudeMeters = json["altitudeMeters"].toDouble();

    return TrackGlobalPosition
    {
        frame, 
        latitudeDegrees, 
        longitudeDegrees, 
        altitudeMeters
    };
}

TrackLocalPosition TrackConverter::localPositionFromJson(const QJsonObject& json)
{
    QString frame = json["frame"].toString();
    double xPosition = json["xPosition"].toDouble();
    double yPosition = json["yPosition"].toDouble();
    double zPosition = json["zPosition"].toDouble();

    return TrackLocalPosition
    {
        frame, 
        xPosition, 
        yPosition, 
        zPosition
    };
}

TrackGlobalVelocity TrackConverter::globalVelocityFromJson(const QJsonObject& json)
{
    double totalVelocityMetersPerSecond = 
        json["totalVelocityMetersPerSecond"].toDouble();
    double groundVelocityMetersPerSecond = 
        json["groundVelocityMetersPerSecond"].toDouble();
    double verticalVelocityMetersPerSecond = 
        json["verticalVelocityMetersPerSecond"].toDouble();

    return TrackGlobalVelocity
    {
        totalVelocityMetersPerSecond, 
        groundVelocityMetersPerSecond, 
        verticalVelocityMetersPerSecond
    };
}

TrackLocalVelocity TrackConverter::localVelocityFromJson(const QJsonObject& json)
{
    double xVelocityMetersPerSecond = 
        json["xVelocityMetersPerSecond"].toDouble();
    double yVelocityMetersPerSecond = 
        json["yVelocityMetersPerSecond"].toDouble();
    double zVelocityMetersPerSecond = 
        json["zVelocityMetersPerSecond"].toDouble();

    return TrackLocalVelocity
    {
        xVelocityMetersPerSecond, 
        yVelocityMetersPerSecond, 
        zVelocityMetersPerSecond
    };
}

QJsonObject TrackConverter::globalPositionToJson(const TrackGlobalPosition& position)
{
    return
    {
        { "frame", position.frame },
        { "latitudeDegrees", position.latitudeDegrees },
        { "longitudeDegrees", position.longitudeDegrees },
        { "altitudeMeters", position.altitudeMeters }
    };
}

QJsonObject TrackConverter::localPositionToJson(const TrackLocalPosition& position)
{
    return
    {
        { "frame", position.frame },
        { "xPosition", position.xPosition },
        { "yPosition", position.yPosition },
        { "zPosition", position.zPosition }
    };
}

QJsonObject TrackConverter::globalVelocityToJson(const TrackGlobalVelocity& velocity)
{
    return
    {
        { "totalVelocityMetersPerSecond", velocity.totalVelocityMetersPerSecond },
        { "groundVelocityMetersPerSecond", velocity.groundVelocityMetersPerSecond },
        { "verticalVelocityMetersPerSecond", velocity.verticalVelocityMetersPerSecond }
    };
}

QJsonObject TrackConverter::localVelocityToJson(const TrackLocalVelocity& velocity)
{
    return
    {
        { "xVelocityMetersPerSecond", velocity.xVelocityMetersPerSecond },
        { "yVelocityMetersPerSecond", velocity.yVelocityMetersPerSecond },
        { "zVelocityMetersPerSecond", velocity.zVelocityMetersPerSecond }
    };
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
        QString icao24 = QString::fromStdString(t.icao24());
        QDateTime timestamp = QDateTime::fromString(QString::fromStdString(t.timestamp()));

        TrackGlobalPosition globalPostion = 
            globalPositionFromProto(t.globalposition());
        TrackLocalPosition localPosition = 
            localPositionFromProto(t.localposition());
        TrackGlobalVelocity globalVelocity = 
            globalVelocityFromProto(t.globalvelocity());
        TrackLocalVelocity localVelocity = 
            localVelocityFromProto(t.localvelocity());

        double headingDegrees = t.headingdegrees();

        tracks.push_back(
            Track(
                icao24, 
                timestamp, 
                globalPostion, 
                localPosition, 
                globalVelocity, 
                localVelocity, 
                headingDegrees
            )
        );
    }

    return tracks;
}

TrackGlobalPosition TrackConverter::globalPositionFromProto
(
    const GlobalPositionProto& globalPosition
)
{
    QString frame = QString::fromStdString(globalPosition.frame());
    double latitudeDegrees = globalPosition.latitudedegrees();
    double longitudeDegrees = globalPosition.longitudedegrees();
    double altitudeMeters = globalPosition.altitudemeters();

    return TrackGlobalPosition
    {
        frame, 
        latitudeDegrees, 
        longitudeDegrees, 
        altitudeMeters
    };
}

TrackLocalPosition TrackConverter::localPositionFromProto
(
    const LocalPositionProto& localPosition
)
{
    QString frame = QString::fromStdString(localPosition.frame());
    double xPosition = localPosition.xposition();
    double yPosition = localPosition.yposition();
    double zPosition = localPosition.zposition();

    return TrackLocalPosition
    {
        frame,
        xPosition,
        yPosition,
        zPosition
    };
}

TrackGlobalVelocity TrackConverter::globalVelocityFromProto
(
    const GlobalVelocityProto& globalVelocity
)
{
    double totalVelocityMetersPerSecond = globalVelocity.totalvelocitymeterspersecond();
    double groundVelocityMetersPerSecond = globalVelocity.groundvelocitymeterspersecond();
    double verticalVelocityMetersPerSecond = globalVelocity.verticalvelocitymeterspersecond();

    return TrackGlobalVelocity
    {
        totalVelocityMetersPerSecond,
        groundVelocityMetersPerSecond,
        verticalVelocityMetersPerSecond
    };
}

TrackLocalVelocity TrackConverter::localVelocityFromProto
(
    const LocalVelocityProto& localVelocity
)
{
    double xVelocityMetersPerSecond = localVelocity.xvelocitymeterspersecond();
    double yVelocityMetersPerSecond = localVelocity.yvelocitymeterspersecond();
    double zVelocityMetersPerSecond = localVelocity.zvelocitymeterspersecond();

    return TrackLocalVelocity
    {
        xVelocityMetersPerSecond,
        yVelocityMetersPerSecond,
        zVelocityMetersPerSecond
    };
}