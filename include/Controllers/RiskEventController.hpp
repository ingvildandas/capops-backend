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
    QHttpServerResponse getMultipleRiskEvents(
        const QHttpServerRequest& request,
        const int count = DEFAULT_COUNT,
        const bool acknowledged = DEFAULT_ACKNOWLEDGED,
        const QString& from = DEFAULT_FROM,
        const QString& to = DEFAULT_TO
    );
    QHttpServerResponse updateRiskEvent(const int id, const QHttpServerRequest& request);
    QHttpServerResponse deleteRiskEvent(const int id, const QHttpServerRequest& request);

private:
    RiskEventService& _service;

public:
    static const int DEFAULT_COUNT = 10;
    static const bool DEFAULT_ACKNOWLEDGED = false;
    inline static const QString DEFAULT_FROM = "";
    inline static const QString DEFAULT_TO = "";
};
