#pragma once

#include <vector>

#include <QString>

#include "Models/Track.hpp"

class TrackData
{
public:
    TrackData
    (
        const int totalAircraftCount,
        const QString& coordinateSystem,
        const std::vector<Track> tracks
    );

    int getTotalAircraftCount() const;
    QString getCoordinateSystem() const;
    std::vector<Track> getTracks() const;

private:
    int _totalAircraftCount;
    QString _coordinateSystem;
    std::vector<Track> _tracks;
};