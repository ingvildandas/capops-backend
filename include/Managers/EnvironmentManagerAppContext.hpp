#pragma once

#include <QString>
#include <QtGlobal>

#include "IEnvironmentManager.hpp"

class EnvironmentManagerAppContext : public IEnvironmentManager
{
public:
    EnvironmentManagerAppContext();

    void loadEnvironmentVariables() const;

    QString getDatabaseFilePath() const override;
    quint16 getHttpPort() const override;
    quint16 getWebSocketPort() const override;
    QString getRedisHost() const override;
    QString getRedisPort() const override;
    int getProtoBufContractVersion() const override;
    int getRestJsonContractVersion() const override;

private:
    mutable QString _databaseFilePath;
    mutable quint16 _httpPort;
    mutable quint16 _webSocketPort;
    mutable QString _redisHost;
    mutable QString _redisPort;
    mutable int _protoBufContractVersion;
    mutable int _restJsonContractVersion;
};