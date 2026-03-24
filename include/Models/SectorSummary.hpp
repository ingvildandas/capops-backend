#pragma once

#include <string>
#include <vector>

#include <QString>

class SectorSummary
{
public:
    explicit SectorSummary(
        const int sectorId,
        const int row,
        const int colunmn,
        const int localAircraftCount,
        const int localAircraftBaseCapacity,
        const int localAircraftEffectiveCapacity,
        const QString& weatherSeverity,
        const QString& riskSeverity,
        const std::vector<std::string>& icao24List
    );

    int getSectorId() const;
    int getRow() const;
    int getColumn() const;
    int getLocalAircraftCount() const;
    int getLocalAircraftBaseCapacity() const;
    int getLocalAircraftEffectiveCapacity() const;
    QString getWeatherSeverity() const;
    QString getRiskSeverity() const;
    std::vector<std::string> getIcao24List() const;

private:
    int _sectorId;
    int _row;
    int _colunmn;
    int _localAircraftCount;
    int _localAircraftBaseCapacity;
    int _localAircraftEffectiveCapacity;
    QString _weatherSeverity;
    QString _riskSeverity;
    std::vector<std::string> _icao24List;
};
