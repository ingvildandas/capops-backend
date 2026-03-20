#include <QString>
#include <QProcessEnvironment>

#include "Managers/EnvironmentManagerAppContext.hpp"

EnvironmentManagerAppContext::EnvironmentManagerAppContext()
{
    loadEnvironmentVariables();
}

void EnvironmentManagerAppContext::loadEnvironmentVariables() const
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    
    _databaseFilePath = env.value("DATABASE_FILE_PATH", "capops.db");
    _httpPort = env.value("HTTP_PORT", "8080").toUShort();
    _webSocketPort = env.value("WEBSOCKET_PORT", "8081").toUShort();
    _redisHost = env.value("REDIS_HOST", "localhost");
    _redisHost = env.value("REDIS_PORT", "6379");
    _protoBufContractVersion = env.value("PROTOBUF_CONTRACT_VERSION", "1").toInt();
    _restJsonContractVersion = env.value("REST_JSON_CONTRACT_VERSION", "1").toInt();
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

QString EnvironmentManagerAppContext::getRedisHost() const
{
    return _redisHost;
}

QString EnvironmentManagerAppContext::getRedisPort() const
{
    return _redisPort;
}

int EnvironmentManagerAppContext::getProtoBufContractVersion() const
{
    return _protoBufContractVersion;
}

int EnvironmentManagerAppContext::getRestJsonContractVersion() const
{
    return _restJsonContractVersion;
}