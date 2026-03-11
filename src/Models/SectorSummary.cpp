#include "Models/SectorSummary.hpp"

SectorSummary::SectorSummary
(
    const int sectorId,
    const int row,
    const int colunmn,
    const int weatherSeverity,
    const double weatherFactor,
    const int localAircraftCount,
    const int localAircraftBaseCapacity,
    const int localAircraftEffectiveCapacity
)   
    :
    _sectorId(sectorId),
    _row(row),
    _colunmn(colunmn),
    _weatherSeverity(weatherSeverity),
    _weatherFactor(weatherFactor),
    _localAircraftCount(localAircraftCount),
    _localAircraftBaseCapacity(localAircraftBaseCapacity),
    _localAircraftEffectiveCapacity(localAircraftEffectiveCapacity)
{}

const int SectorSummary::getSectorId() const
{
    return _sectorId;
}

const int SectorSummary::getRow() const
{
    return _row;
}

const int SectorSummary::getColunmn() const
{
    return _colunmn;
}

const int SectorSummary::getWeatherSeverity() const
{
    return _weatherSeverity;
}

const double SectorSummary::getWeatherFactor() const
{
    return _weatherFactor;
}

const int SectorSummary::getLocalAircraftCount() const
{
    return _localAircraftCount;
}

const int SectorSummary::getLocalAircraftBaseCapacity() const
{
    return _localAircraftBaseCapacity;
}

const int SectorSummary::getLocalAircraftEffectiveCapacity() const
{
    return _localAircraftEffectiveCapacity;
}
