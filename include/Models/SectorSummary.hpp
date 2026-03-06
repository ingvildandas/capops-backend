#pragma once

class SectorSummary
{
public:
    explicit SectorSummary(
        const int sectorId,
        const int row,
        const int colunmn,
        const int weatherSeverity,
        const double weatherFactor,
        const int localAircraftCount,
        const int localAircraftBaseCapacity,
        const int localAircraftEffectiveCapacity
    );

    const int getSectorId() const;
    const int getRow() const;
    const int getColunmn() const;
    const int getWeatherSeverity() const;
    const double getWeatherFactor() const;
    const int getLocalAircraftCount() const;
    const int getLocalAircraftBaseCapacity() const;
    const int getLocalAircraftEffectiveCapacity() const;

private:
    int _sectorId;
    int _row;
    int _colunmn;
    int _weatherSeverity;
    double _weatherFactor;
    int _localAircraftCount;
    int _localAircraftBaseCapacity;
    int _localAircraftEffectiveCapacity;
};
