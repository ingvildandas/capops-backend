#pragma once

#include <QDateTime>
#include <QString>

#include "Structs/TrackStructs.hpp"

class Track
{
public:
    explicit Track(
        const QString& icao24,
        const QDateTime& timestamp,
        const TrackPosition& position,
        const TrackVelocity& velocity,
        const double headingDegrees,
        const double groundTrackDegrees
    );

    const QString& getIcao24() const;
    const QDateTime& getTimestamp() const;
    const TrackPosition& getPosition() const;
    const TrackVelocity& getVelocity() const;
    const double getHeadingDegrees() const;
    const double getGroundTrackDegrees() const;

private:
    QString _icao24;
    QDateTime _timestamp;
    TrackPosition _position;
    TrackVelocity _velocity;
    double _headingDegrees;
    double _groundTrackDegrees;
};