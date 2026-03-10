#pragma once

#include <QObject>
#include <QHttpServerRequest>
#include <QHttpServerResponse>

class RiskEventService;

class RiskEventController : public QObject
{
    Q_OBJECT

public:
    explicit RiskEventController(
        RiskEventService& service,
        QObject* parent = nullptr
    );

    QHttpServerResponse getRiskEvent(const int id, const QHttpServerRequest& request);
    QHttpServerResponse getMostRecentRiskEvents(const QHttpServerRequest& request);
    QHttpServerResponse getMostRecentRiskEvents
    (
        const int count, 
        const QHttpServerRequest& request
    );
    QHttpServerResponse getRiskEventsBetween
    (
        const QString& from, 
        const QString& to, 
        const QHttpServerRequest& request
    );
    QHttpServerResponse updateRiskEvent(const int id, const QHttpServerRequest& request);
    QHttpServerResponse deleteRiskEvent(const int id, const QHttpServerRequest& request);

private:
    RiskEventService& _service;
};
