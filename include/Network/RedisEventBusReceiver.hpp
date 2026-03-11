#pragma once

#include <atomic>
#include <memory>
#include <thread>

#include <QObject>

#include <sw/redis++/redis++.h>

#include "Managers/WebSocketSessionManager.hpp"
#include "Services/RiskEventService.hpp"
#include "Services/SectorSummaryService.hpp"
#include "Services/TrackService.hpp"

class FlightDataDto;
class QString;

class RedisEventBusReceiver
{
    Q_OBJECT

public:
    RedisEventBusReceiver
    (
        const QString& redisUri,
        WebSocketSessionManager& sessionManager,
        RiskEventService& riskEventService,
        SectorSummaryService& sectorSummaryService,
        TrackService& trackService,
        QObject* parent = nullptr
    );
    ~RedisEventBusReceiver();

    void start();
    void stop();

private:
    void runSubscriber();
    void handleMessage(const QString& channel, const QString& payload);

    FlightDataDto deserialize(const QString& payload);

private:
    QString _redisUri;

    WebSocketSessionManager& _sessionManager;
    SectorSummaryService& _sectorSummaryService;
    TrackService& _trackService;
    RiskEventService& _riskEventService;

    std::unique_ptr<sw::redis::Redis> _redis;

    std::thread _subscriberThread;
    std::atomic<bool> _running = false;
};
