#include <vector>

#include <QString>

#include "Models/TrackData.hpp"
#include "Models/Track.hpp"

TrackData::TrackData
(
    const int totalAircraftCount,
    const QString& coordinateSystem,
    const std::vector<Track> tracks
)
    :
    _totalAircraftCount(totalAircraftCount),
    _coordinateSystem(coordinateSystem),
    _tracks(tracks)
{}

int TrackData::getTotalAircraftCount() const
{
    return _totalAircraftCount;
}

QString TrackData::getCoordinateSystem() const
{
    return _coordinateSystem;
}

std::vector<Track> TrackData::getTracks() const
{
    return _tracks;
}