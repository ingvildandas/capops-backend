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

    int httpPort = settings.value("HTTP_PORT").toInt(&ok);
    if (!ok || httpPort <= 0) {
        throw FileException("HTTP_PORT must be a positive integer.");
    }

    int webSocketPort = settings.value("WEBSOCKET_PORT").toInt(&ok);
    if (!ok || webSocketPort <= 0) {
        throw FileException("WEBSOCKET_PORT must be a positive integer.");
    }

    int protoBufContractVersion = settings.value("PROTOBUF_CONTRACT_VERSION").toInt(&ok);
    if (!ok || protoBufContractVersion <= 0) {
        throw FileException("PROTOBUF_CONTRACT_VERSION must be a positive integer.");
    }

    int restJsonContractVersion = settings.value("REST_JSON_CONTRACT_VERSION").toInt(&ok);
    if (!ok ||restJsonContractVersion <= 0) {
        throw FileException("REST_JSON_CONTRACT_VERSION must be a positive integer.");
    }

    _databaseFilePath = databaseFilePath;
    _httpPort = httpPort;
    _webSocketPort = webSocketPort;
    _protoBufContractVersion = protoBufContractVersion;
    _restJsonContractVersion = restJsonContractVersion;
}

QString EnvironmentManager::getDatabaseFilePath() const
{
    return _databaseFilePath;
}

int EnvironmentManager::getHttpPort() const
{
    return _httpPort;
}

int EnvironmentManager::getWebSocketPort() const
{
    return _webSocketPort;
}

int EnvironmentManager::getProtoBufContractVersion() const
{
    return _protoBufContractVersion;
}

int EnvironmentManager::getRestJsonContractVersion() const
{
    return _restJsonContractVersion;
}