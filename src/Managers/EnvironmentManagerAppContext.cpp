#include <QString>

#include "EnvironmentManagerAppContext.hpp"

void EnvironmentManagerAppContext::loadEnvironmentVariables()
{
    _databaseFilePath = qgetenv("DATABASE_FILE_PATH");
    _httpPort = static_cast<quint16>(qgetenv("HTTP_PORT").toUShort());
    _webSocketPort = static_cast<quint16>(qgetenv("WEBSOCKET_PORT").toUShort());
    _redisUri = qgetenv("REDIS_URI");
    _protoBufContractVersion = qgetenv("PROTOBUF_CONTRACT_VERSION").toInt();
    _restJsonContractVersion = qgetenv("REST_JSON_CONTRACT_VERSION").toInt();
}

QString EnvironmentManagerAppContext::getDatabaseFilePath() const
{
    return _databaseFilePath;
}

quint16 EnvironmentManagerAppContext::getHttpPort() const
{
    return _httpPort;
}

quint16 EnvironmentManagerAppContext::getWebSocketPort() const
{
    return _webSocketPort;
}

QString EnvironmentManagerAppContext::getRedisUri() const
{
    return _redisUri;
}

int EnvironmentManagerAppContext::getProtoBufContractVersion() const
{
    return _protoBufContractVersion;
}

int EnvironmentManagerAppContext::getRestJsonContractVersion() const
{
    return _restJsonContractVersion;
}