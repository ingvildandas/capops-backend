#include <QString>

#include "Models/SectorSummary.hpp"

SectorSummary::SectorSummary
(
    const int sectorId,
    const int row,
    const int colunmn,
    const int localAircraftCount,
    const int localAircraftBaseCapacity,
    const int localAircraftEffectiveCapacity,
    const QString& weatherSeverity,
    const QString& riskSeverity,
    const QVector<QString>& icao24List
)   
    :
    _sectorId(sectorId),
    _row(row),
    _colunmn(colunmn),
    _localAircraftCount(localAircraftCount),
    _localAircraftBaseCapacity(localAircraftBaseCapacity),
    _localAircraftEffectiveCapacity(localAircraftEffectiveCapacity),
    _weatherSeverity(weatherSeverity),
    _riskSeverity(riskSeverity),
    _icao24List(icao24List)
{}

int SectorSummary::getSectorId() const
{
    return _sectorId;
}

int SectorSummary::getRow() const
{
    return _row;
}

int SectorSummary::getColumn() const
{
    return _colunmn;
}

int SectorSummary::getLocalAircraftCount() const
{
    return _localAircraftCount;
}

int SectorSummary::getLocalAircraftBaseCapacity() const
{
    return _localAircraftBaseCapacity;
}

int SectorSummary::getLocalAircraftEffectiveCapacity() const
{
    return _localAircraftEffectiveCapacity;
}

QString SectorSummary::getWeatherSeverity() const
{
    return _weatherSeverity;
}

QString SectorSummary::getRiskSeverity() const
{
    return _riskSeverity;
}

QVector<QString> SectorSummary::getIcao24List() const
{
    return _icao24List;
}
