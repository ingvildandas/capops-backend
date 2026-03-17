#pragma once

#include <QString>

struct TrackPosition
{
    const double latitudeDegrees;
    const double longitudeDegrees;
    const double altitudeMeters;
};

struct TrackVelocity
{
    const double groundSpeedKnots;
    const double verticalSpeedFeetPerMinute;
};