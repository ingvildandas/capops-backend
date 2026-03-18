#pragma once

#include <QString>

class EnvironmentManager
{
public:
    EnvironmentManager(const QString& envFilePath);

    void loadEnvironmentVariables(const QString& envFilePath);

    QString getDatabaseFilePath() const;
    quint16 getHttpPort() const;
    quint16 getWebSocketPort() const;
    QString getRedisUri() const;
    int getProtoBufContractVersion() const;
    int getRestJsonContractVersion() const;

private:
    QString _databaseFilePath;
    quint16 _httpPort;
    quint16 _webSocketPort;
    QString _redisUri;
    int _protoBufContractVersion;
    int _restJsonContractVersion;
};