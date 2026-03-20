#include <QString>

#include "Managers/EnvironmentManagerAppContext.hpp"

QString EnvironmentManagerAppContext::getDatabaseFilePath() const
{
    return "capaops.db";
}

quint16 EnvironmentManagerAppContext::getHttpPort() const
{
    return 8080;
}

quint16 EnvironmentManagerAppContext::getWebSocketPort() const
{
    return 8081;
}

QString EnvironmentManagerAppContext::getRedisUri() const
{
    return "redis://localhost:6379";
}

int EnvironmentManagerAppContext::getProtoBufContractVersion() const
{
    return 1;
}

int EnvironmentManagerAppContext::getRestJsonContractVersion() const
{
    return 1;
}