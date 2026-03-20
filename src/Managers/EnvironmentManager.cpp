#include <QSettings>
#include <QString>

#include "Managers/EnvironmentManager.hpp"
#include "Exceptions/FileException.hpp"

EnvironmentManager::EnvironmentManager(const QString& envFilePath)
{
    loadEnvironmentVariables(envFilePath);
}

void EnvironmentManager::loadEnvironmentVariables(const QString& envFilePath)
{
    QSettings settings(envFilePath, QSettings::IniFormat);
    
    bool ok;
    QString databaseFilePath = settings.value("DATABASE_FILE_PATH").toString();
    if (databaseFilePath.isEmpty()) {
        throw FileException("DATABASE_FILE_PATH is missing or empty.");
    }
    _databaseFilePath = databaseFilePath;

    int httpPort = settings.value("HTTP_PORT").toInt(&ok);
    if (!ok || httpPort <= 0) {
        throw FileException("HTTP_PORT must be a positive integer.");
    }
    try
    {
        _httpPort = static_cast<quint16>(httpPort);
    }
    catch(const std::exception&)
    {
        throw FileException("HTTP_PORT value is out of range for quint16.");
    }
    
    int webSocketPort = settings.value("WEBSOCKET_PORT").toInt(&ok);
    if (!ok || webSocketPort <= 0) {
        throw FileException("WEBSOCKET_PORT must be a positive integer.");
    }
    try
    {
        _webSocketPort = static_cast<quint16>(webSocketPort);
    }
    catch(const std::exception&)
    {
        throw FileException("WEBSOCKET_PORT value is out of range for quint16.");
    }

    QString redisHost = settings.value("REDIS_HOST").toString();
    if (redisHost.isEmpty()) {
        throw FileException("REDIS_HOST is missing or empty.");
    }
    _redisHost = redisHost;

    QString redisPort = settings.value("REDIS_PORT").toString();
    if (redisPort.isEmpty()) {
        throw FileException("REDIS_PORT is missing or empty.");
    }
    _redisPort = redisPort;

    int protoBufContractVersion = settings.value("PROTOBUF_CONTRACT_VERSION").toInt(&ok);
    if (!ok || protoBufContractVersion <= 0) {
        throw FileException("PROTOBUF_CONTRACT_VERSION must be a positive integer.");
    }
    _protoBufContractVersion = protoBufContractVersion;

    int restJsonContractVersion = settings.value("REST_JSON_CONTRACT_VERSION").toInt(&ok);
    if (!ok ||restJsonContractVersion <= 0) {
        throw FileException("REST_JSON_CONTRACT_VERSION must be a positive integer.");
    }
    _restJsonContractVersion = restJsonContractVersion;
}

QString EnvironmentManager::getDatabaseFilePath() const
{
    return _databaseFilePath;
}

quint16 EnvironmentManager::getHttpPort() const
{
    return _httpPort;
}

quint16 EnvironmentManager::getWebSocketPort() const
{
    return _webSocketPort;
}

QString EnvironmentManager::getRedisHost() const
{
    return _redisHost;
}

QString EnvironmentManager::getRedisPort() const
{
    return _redisPort;
}

int EnvironmentManager::getProtoBufContractVersion() const
{
    return _protoBufContractVersion;
}

int EnvironmentManager::getRestJsonContractVersion() const
{
    return _restJsonContractVersion;
}