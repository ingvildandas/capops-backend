#pragma once

#include <QtGlobal>

class QString;

class IEnvironmentManager
{
public:
    virtual ~IEnvironmentManager() = default;

    virtual QString getDatabaseFilePath() const = 0;
    virtual quint16 getHttpPort() const = 0;
    virtual quint16 getWebSocketPort() const = 0;
    virtual QString getRedisHost() const = 0;
    virtual QString getRedisPort() const = 0;
    virtual int getProtoBufContractVersion() const = 0;
    virtual int getRestJsonContractVersion() const = 0;
};