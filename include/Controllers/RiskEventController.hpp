#pragma once

#include <QObject>
#include <QHttpServerRequest>
#include <QHttpServerResponse>

class FlightDataStateManager;
class RiskEventService;

class RiskEventController : public QObject
{
    Q_OBJECT

public:
    explicit RiskEventController(
        RiskEventService& service,
        FlightDataStateManager& stateManager,
        QObject* parent = nullptr
    );

    QHttpServerResponse getRiskEvent
    (
        const int riskEventid, 
        const QHttpServerRequest& request
    );
    QHttpServerResponse getMultipleRiskEvents(
        const QHttpServerRequest& request,
        const int count = DEFAULT_COUNT,
        const bool acknowledged = DEFAULT_ACKNOWLEDGED,
        const QString& from = DEFAULT_FROM,
        const QString& to = DEFAULT_TO
    );
    QHttpServerResponse updateRiskEvent
    (
        const int riskEventId, 
        const QHttpServerRequest& request
    );
    QHttpServerResponse deleteRiskEvent
    (
        const int riskEventId, 
        const QHttpServerRequest& request
    );

private:
    RiskEventService& _service;
    FlightDataStateManager& _stateManager;

public:
    static const int DEFAULT_COUNT = 1000;
    static const bool DEFAULT_ACKNOWLEDGED = false;
    inline static const QString DEFAULT_FROM = "";
    inline static const QString DEFAULT_TO = "";
};
