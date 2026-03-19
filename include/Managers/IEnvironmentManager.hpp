#pragma once

#include <QtGlobal>

class QString;

class IEnvironmentManager
{
public:
    virtual ~IEnvironmentManager() = default;

    virtual void loadEnvironmentVariables(const QString& envFilePath) = 0;

    virtual QString getDatabaseFilePath() const = 0;
    virtual quint16 getHttpPort() const = 0;
    virtual quint16 getWebSocketPort() const = 0;
    virtual QString getRedisUri() const = 0;
    virtual int getProtoBufContractVersion() const = 0;
    virtual int getRestJsonContractVersion() const = 0;
};