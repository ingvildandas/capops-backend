#include <QDateTime>
#include <QString>

#include "Models/Track.hpp"

Track::Track(
    const QString& icao24,
    const QDateTime& timestamp,
    const TrackGlobalPosition& globalPosition,
    const TrackLocalPosition& localPosition,
    const TrackGlobalVelocity& globalVelocity,
    const TrackLocalVelocity& localVelocity, 
    const double headingDegrees
)
    : 
    _icao24(icao24),
    _timestamp(timestamp),
    _globalPosition(globalPosition),
    _localPosition(localPosition),
    _globalVelocity(globalVelocity),
    _localVelocity(localVelocity),
    _headingDegrees(headingDegrees)
{}

const QString& Track::getIcao24() const
{
    return _icao24;
}

const QDateTime& Track::getTimestamp() const
{
    return _timestamp;
}

const TrackGlobalPosition& Track::getGlobalPosition() const
{
    return _globalPosition;
}

const TrackLocalPosition& Track::getLocalPosition() const
{
    return _localPosition;
}

const TrackGlobalVelocity& Track::getGlobalVelocity() const
{
    return _globalVelocity;
}

const TrackLocalVelocity& Track::getLocalVelocity() const
{
    return _localVelocity;
}

const double Track::getHeadingDegrees() const
{
    return _headingDegrees;
}