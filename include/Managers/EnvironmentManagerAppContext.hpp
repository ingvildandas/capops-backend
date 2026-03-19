#pragma once

#include <QString>
#include <QtGlobal>

#include "IEnvironmentManager.hpp"

class EnvironmentManagerAppContext : public IEnvironmentManager
{
public:
    EnvironmentManagerAppContext() = default;

    void loadEnvironmentVariables();

    QString getDatabaseFilePath() const override;
    quint16 getHttpPort() const override;
    quint16 getWebSocketPort() const override;
    QString getRedisUri() const override;
    int getProtoBufContractVersion() const override;
    int getRestJsonContractVersion() const override;

private:
    QString _databaseFilePath;
    quint16 _httpPort;
    quint16 _webSocketPort;
    QString _redisUri;
    int _protoBufContractVersion;
    int _restJsonContractVersion;
};