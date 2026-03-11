#pragma once

#include "Structs/TrackStructs.hpp"

class QDateTime;
class QString;

class Track
{
public:
    explicit Track(
        const QString& icao24,
        const QDateTime& timestamp,
        const TrackGlobalPosition& globalPosition,
        const TrackLocalPosition& localPosition,
        const TrackGlobalVelocity& globalVelocity,
        const TrackLocalVelocity& localVelocity, 
        const double headingDegrees
    );

    const QString& getIcao24() const;
    const QDateTime& getTimestamp() const;
    const TrackGlobalPosition& getGlobalPosition() const;
    const TrackLocalPosition& getLocalPosition() const;
    const TrackGlobalVelocity& getGlobalVelocity() const;
    const TrackLocalVelocity& getLocalVelocity() const;
    const double getHeadingDegrees() const;

private:
    QString _icao24;
    QDateTime _timestamp;
    TrackGlobalPosition _globalPosition;
    TrackLocalPosition _localPosition;
    TrackGlobalVelocity _globalVelocity;
    TrackLocalVelocity _localVelocity;
    double _headingDegrees;

private:
    void validateGlobalPosition(const TrackGlobalPosition globalPosition);
    void validateLocalPosition(const TrackLocalPosition localPosition);
    void validateGlobalVelocity(const TrackGlobalVelocity globalVelocity);
    void validateLocalVelocity(const TrackLocalVelocity localVelocity);
};