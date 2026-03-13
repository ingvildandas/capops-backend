#include <atomic>
#include <memory>
#include <thread>

#include <QObject>
#include <QString>

#include <sw/redis++/redis++.h>

#include "Network/RedisEventBusReceiver.hpp"
#include "Converters/FlightDataDtoConverter.hpp"
#include "Converters/MetadataConverter.hpp"
#include "Converters/RiskEventConverter.hpp"
#include "Converters/SectorSummaryConverter.hpp"
#include "Converters/TrackConverter.hpp"
#include "Dtos/FlightDataDto.hpp"
#include "Managers/WebSocketSessionManager.hpp"
#include "Models/Metadata.hpp"
#include "Models/RiskEvent.hpp"
#include "Models/SectorSummary.hpp"
#include "Models/Track.hpp"
#include "Proto/FlightData.hpp"
#include "Services/RiskEventService.hpp"
#include "Services/SectorSummaryService.hpp"
#include "Services/TrackService.hpp"

RedisEventBusReceiver::RedisEventBusReceiver
(
    const QString& redisUri,
    WebSocketSessionManager& sessionManager,
    RiskEventService& riskEventService,
    SectorSummaryService& sectorSummaryService,
    TrackService& trackService,
    QObject* parent
)
    :
    _redisUri(redisUri),
    _sessionManager(sessionManager),
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

    _redis = std::make_unique<sw::redis::Redis>(_redisUri.toStdString());
    _running = true;

    _subscriberThread = std::thread([this]()
    {
        runSubscriber();
    });
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

void RedisEventBusReceiver::handleMessage(const std::string& channel, const std::string& payload)
{
    try
    {
        auto dto = deserialize(payload);

        if (!dto.getTracks().empty())
        {
            _trackService.updateState(dto.getTracks());
        }

        if (!dto.getSectorSummaries().empty())
            _sectorSummaryService.updateState(dto.getSectorSummaries());

        if (!dto.getSectorSummaries().empty())
            _riskEventService.updateState(dto.getRiskEvents());

        _sessionManager.broadcast(dto);
    }
    catch (const std::exception& e)
    {
        qWarning() << "Event bus error: " << e.what();
    }
}

FlightDataDto RedisEventBusReceiver::deserialize
(
    const std::string& payload
)
{
    FlightData proto;

    if (!proto.ParseFromString(payload))
    {
        throw std::runtime_error("Invalid FlightData protobuf");
    }

    Metadata metadata = MetadataConverter::fromProto(proto.metadata());

    std::vector<Track> tracks = 
        TrackConverter::fromProto(proto.tracks());
    std::vector<SectorSummary> sectorSummaries = 
        SectorSummaryConverter::fromProto(proto.sector_summaries());
    std::vector<RiskEvent> riskEvents = 
        RiskEventConverter::fromProto(proto.risk_events());

    return FlightDataDto(metadata, riskEvents, sectorSummaries, tracks);
}