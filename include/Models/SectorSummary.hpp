#pragma once

#include <string>
#include <vector>

#include <QString>
#include <QVector>

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
        const QVector<QString>& icao24List
    );

    int getSectorId() const;
    int getRow() const;
    int getColumn() const;
    int getLocalAircraftCount() const;
    int getLocalAircraftBaseCapacity() const;
    int getLocalAircraftEffectiveCapacity() const;
    QString getWeatherSeverity() const;
    QString getRiskSeverity() const;
    QVector<QString> getIcao24List() const;

private:
    int _sectorId;
    int _row;
    int _colunmn;
    int _localAircraftCount;
    int _localAircraftBaseCapacity;
    int _localAircraftEffectiveCapacity;
    QString _weatherSeverity;
    QString _riskSeverity;
    QVector<QString> _icao24List;
};
