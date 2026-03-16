#pragma once

#include <atomic>
#include <memory>
#include <thread>

#include <QObject>

#include <sw/redis++/redis++.h>

#include "Managers/WebSocketSessionManager.hpp"
#include "Services/MetadataService.hpp"
#include "Services/RiskEventService.hpp"
#include "Services/SectorSummaryService.hpp"
#include "Services/TrackService.hpp"

class FlightDataDto;
class QString;

class RedisEventBusReceiver : public QObject
{
    Q_OBJECT

public:
    RedisEventBusReceiver
    (
        const QString& redisUri,
        WebSocketSessionManager& sessionManager,
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

    FlightDataDto deserialize(const std::string& payload);

private:
    QString _redisUri;

    WebSocketSessionManager& _sessionManager;
    MetadataService& _metadataService;
    SectorSummaryService& _sectorSummaryService;
    TrackService& _trackService;
    RiskEventService& _riskEventService;

    std::unique_ptr<sw::redis::Redis> _redis;

    std::thread _subscriberThread;
    std::atomic<bool> _running = false;
};
