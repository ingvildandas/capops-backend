#pragma once

#include <atomic>
#include <memory>
#include <thread>

#include <QObject>

#include <sw/redis++/redis++.h>

#include "Managers/FlightDataStateManager.hpp"
#include "Managers/WebSocketSessionManager.hpp"
#include "Services/MetadataService.hpp"
#include "Services/RiskEventService.hpp"
#include "Services/SectorSummaryService.hpp"
#include "Services/TrackService.hpp"

class FlightData;
class QString;

class RedisEventBusReceiver : public QObject
{
    Q_OBJECT

public:
    RedisEventBusReceiver
    (
        const QString& redisHost,
        const QString& redisPort,
        WebSocketSessionManager& sessionManager,
        FlightDataStateManager& flightDataStateManager,
        MetadataService& metadataService,
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
    void handleMessage(const std::string& channel, const std::string& payload);

    FlightData deserialize(const std::string& payload);

private:
    QString _redisHost;
    QString _redisPort;

    WebSocketSessionManager& _sessionManager;
    FlightDataStateManager& _flightDataStateManager;
    MetadataService& _metadataService;
    SectorSummaryService& _sectorSummaryService;
    TrackService& _trackService;
    RiskEventService& _riskEventService;

    std::unique_ptr<sw::redis::Redis> _redis;

    std::thread _subscriberThread;
    std::atomic<bool> _running = false;
};
