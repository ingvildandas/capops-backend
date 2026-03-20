#pragma once

#include <QString>
#include <QtGlobal>

#include "IEnvironmentManager.hpp"

class EnvironmentManager : public IEnvironmentManager
{
public:
    EnvironmentManager(const QString& envFilePath);

    void loadEnvironmentVariables(const QString& envFilePath);

    QString getDatabaseFilePath() const override;
    quint16 getHttpPort() const override;
    quint16 getWebSocketPort() const override;
    QString getRedisHost() const override;
    QString getRedisPort() const override;
    int getProtoBufContractVersion() const override;
    int getRestJsonContractVersion() const override;

private:
    QString _databaseFilePath;
    quint16 _httpPort;
    quint16 _webSocketPort;
    QString _redisHost;
    QString _redisPort;
    int _protoBufContractVersion;
    int _restJsonContractVersion;
};