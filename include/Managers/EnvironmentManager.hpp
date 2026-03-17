#pragma once

#include <QString>

class EnvironmentManager
{
public:
    EnvironmentManager() = default;

    void loadEnvironmentVariables(const QString& envFilePath);

    QString getDatabaseFilePath() const;
    int getHttpPort() const;
    int getWebSocketPort() const;
    int getProtoBufContractVersion() const;
    int getRestJsonContractVersion() const;

private:
    QString _databaseFilePath;
    int _httpPort;
    int _webSocketPort;
    int _protoBufContractVersion;
    int _restJsonContractVersion;
};