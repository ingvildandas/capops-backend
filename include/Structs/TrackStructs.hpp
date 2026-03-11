#pragma once

#include <QString>

struct TrackGlobalPosition
{
    const QString frame;
    const double latitudeDegrees;
    const double longitudeDegrees;
    const double altitudeMeters;
};

struct TrackLocalPosition
{
    const QString frame;
    const double xPosition;
    const double yPosition;
    const double zPosition;
};

struct TrackGlobalVelocity
{
    const double totalVelocityMetersPerSecond;
    const double groundVelocityMetersPerSecond;
    const double verticalVelocityMetersPerSecond;
};

struct TrackLocalVelocity
{
    const double xVelocityMetersPerSecond;
    const double yVelocityMetersPerSecond;
    const double zVelocityMetersPerSecond;
};