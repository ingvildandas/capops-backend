#pragma once

#include <chrono>
#include <string>

class Track
{
public:
    Track(
        const std::string& icao24,
        const std::chrono::system_clock::time_point& timestamp,
        const std::string& positionFrame,
        const double latitudeDegrees,
        const double longitudeDegrees,
        const double altitudeMeters,
        const std::string& velocityFrame,
        const double velocityMetersPerSecond,
        const double xVelocityMetersPerSecond,
        const double yVelocityMetersPerSecond,
        const double zVelocityMetersPerSecond,
        const double headingDegrees
    );

    std::string getIcao24();
    std::chrono::system_clock::time_point getTimestamp();
    std::string getPositionFrame();
    double getLatitudeDegrees();
    double getLongitudeDegrees();
    double getAltitudeMeters();
    std::string velocityFrame();
    double getVelocityMetersPerSecond();
    double getXVelocityMetersPerSecond();
    double getYVelocityMetersPerSecond();
    double getZVelocityMetersPerSecond();
    double getHeadingDegrees();

private:
    std::string _icao24;
    std::chrono::system_clock::time_point _timestamp;
    std::string positionFrame;
    double _latitudeDegrees;
    double _longitudeDegrees;
    double _altitudeMeters;
    std::string _velocityFrame;
    double _velocityMetersPerSecond;
    double _xVelocityMetersPerSecond;
    double _yVelocityMetersPerSecond;
    double _zVelocityMetersPerSecond;
    double _headingDegrees;
};