#pragma once

#include <chrono>
#include <string>

#include "Structs/TrackStructs.hpp";

class Track
{
public:
    explicit Track(
        const std::string& icao24,
        const std::chrono::system_clock::time_point& timestamp,
        const TrackGlobalPosition& globalPosition,
        const TrackLocalPosition& localPosition,
        const TrackGlobalVelocity& globalVelocity,
        const TrackLocalVelocity& localVelocity, 
        const double headingDegrees
    );

    const std::string& getIcao24() const;
    const std::chrono::system_clock::time_point& getTimestamp() const;
    const TrackGlobalPosition& getGlobalPosition() const;
    const TrackLocalPosition& getLocalPosition() const;
    const TrackGlobalVelocity& getGlobalVelocity() const;
    const TrackLocalVelocity& getLocalVelocity() const;
    const double getHeadingDegrees() const;

private:
    std::string _icao24;
    std::chrono::system_clock::time_point _timestamp;
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