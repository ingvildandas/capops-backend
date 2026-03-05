#pragma once

#include <QObject>
#include <QHttpServerRequest>
#include <QHttpServerResponse>

class RiskEventService;
class SectorSummaryService;
class TrackService;

class FlightDataController : public QObject
{
    Q_OBJECT

public:
    explicit FlightDataController(
        QObject *parent = nullptr
    );
    ~FlightDataController() override;

    QHttpServerResponse openConnection(const QHttpServerRequest& request);
    QHttpServerResponse closeConnection(const QHttpServerRequest& request);
    
};
