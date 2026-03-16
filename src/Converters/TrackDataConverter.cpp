#include <vector>

#include <QJsonObject>
#include <QString>

#include "Converters/TrackDataConverter.hpp"
#include "Converters/TrackConverter.hpp"
#include "Models/Track.hpp"
#include "Models/TrackData.hpp"
#include "Proto/FlightData.hpp"

TrackData TrackDataConverter::fromJson(const QJsonObject& json)
{
    int totalAircraftCount = json["totalAircraftCount"].toInt();
    QString coordinateSystem = json["coordinateSystem"].toString();
    std::vector<Track> tracks = TrackConverter::fromJson(json["tracks"].toArray());

    return TrackData(totalAircraftCount, coordinateSystem, tracks);
}

QJsonObject TrackDataConverter::toJson(const TrackData& trackData)
{
    return QJsonObject
    {
        { "totalAircraftCount", trackData.getTotalAircraftCount() },
        { "coordinateSystem", trackData.getCoordinateSystem() },
        { "tracks", TrackConverter::toJson(trackData.getTracks()) }
    };
}

TrackData TrackDataConverter::fromProto(const TrackDataProto& protoTrackData)
{
    int totalAircraftCount = protoTrackData.totalaircraftcount();
    QString coordinateSystem = QString::fromStdString(protoTrackData.coordinatesystem());
    std::vector<Track> tracks = TrackConverter::fromProto(protoTrackData.tracks());

    return TrackData(totalAircraftCount, coordinateSystem, tracks);
}
