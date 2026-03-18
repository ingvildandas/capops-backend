#include <atomic>
#include <memory>
#include <thread>

#include <QObject>
#include <QString>

#include <sw/redis++/redis++.h>

#include "Network/RedisEventBusReceiver.hpp"
#include "Converters/FlightDataConverter.hpp"
#include "Exceptions/DatabaseException.hpp"
#include "Exceptions/RedisEventBusException.hpp"
#include "Models/FlightData.hpp"
#include "Managers/FlightDataStateManager.hpp"
#include "Managers/WebSocketSessionManager.hpp"
#include "Models/Metadata.hpp"
#include "Models/RiskEvent.hpp"
#include "Models/RiskEventData.hpp"
#include "Models/SectorSummary.hpp"
#include "Models/SectorSummaryData.hpp"
#include "Models/Track.hpp"
#include "Models/TrackData.hpp"
#include "Proto/FlightData.hpp"
#include "Services/RiskEventService.hpp"
#include "Services/SectorSummaryService.hpp"
#include "Services/TrackService.hpp"

RedisEventBusReceiver::RedisEventBusReceiver
(
    const QString& redisUri,
    WebSocketSessionManager& sessionManager,
    FlightDataStateManager& flightDataStateManager,
    MetadataService& metadataService,
    RiskEventService& riskEventService,
    SectorSummaryService& sectorSummaryService,
    TrackService& trackService,
    QObject* parent
)
    :
    _redisUri(redisUri),
    _sessionManager(sessionManager),
    _flightDataStateManager(flightDataStateManager),
    _metadataService(metadataService),
    _sectorSummaryService(sectorSummaryService),
    _trackService(trackService),
    _riskEventService(riskEventService),
    QObject(parent)
{}

RedisEventBusReceiver::~RedisEventBusReceiver()
{
    stop();
}

void RedisEventBusReceiver::start()
{
    if (_running) return;

    ping();
    _redis = std::make_unique<sw::redis::Redis>(_redisUri.toStdString());
    _running = true;

    _subscriberThread = std::thread([this]()
    {
        runSubscriber();
    });
}

void RedisEventBusReceiver::ping()
{
    if (_redis)
    {
        try
        {
            _redis->ping();
        }
        catch (const sw::redis::Error &e)
        {
            throw RedisEventBusException(e.what());
        }
    }
}

void RedisEventBusReceiver::stop()
{
    _running = false;

    if (_subscriberThread.joinable())
    {
        _subscriberThread.join();
    }
}

void RedisEventBusReceiver::runSubscriber()
{
    auto sub = _redis->subscriber();

    sub.on_message([this](std::string channel, std::string msg)
    {
        handleMessage(channel, msg);
    });

    sub.subscribe("flightdata");

    while (_running)
    {
        try
        {
            sub.consume();
        }
        catch (const sw::redis::Error &e)
        {
            qWarning() << "Redis error:" << e.what();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

void RedisEventBusReceiver::handleMessage
(
    const std::string& channel, 
    const std::string& payload
)
{
    try
    {
        auto flightData = deserialize(payload);

        _metadataService.updateState
        (
            flightData.getMetadata(),
            _flightDataStateManager
        );
        _trackService.updateState
        (
            flightData.getTrackData(),
            _flightDataStateManager
        );
        _sectorSummaryService.updateState
        (
            flightData.getSectorSummaryData(),
            _flightDataStateManager
        );
        _riskEventService.updateState
        (
            flightData.getRiskEventData(),
            _flightDataStateManager
        );

        auto updatedState = _flightDataStateManager.getState();

        _sessionManager.broadcast(updatedState);
    }
    catch (const DatabaseException& e)
    {
        qWarning() << e.what();
    }
    catch (const RedisEventBusException& e)
    {
        qWarning() << e.what();
    }
    catch (const std::exception& e)
    {
        qWarning() << "Unexpected error occurred: " << e.what();
    }
}

FlightData RedisEventBusReceiver::deserialize
(
    const std::string& payload
)
{
    FlightDataProto proto;

    if (!proto.ParseFromString(payload))
    {
        throw RedisEventBusException("Invalid FlightData protobuf");
    }

    return FlightDataConverter::fromProto(proto);
}