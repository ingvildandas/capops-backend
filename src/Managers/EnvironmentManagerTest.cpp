#include <QString>

#include "Managers/EnvironmentManagerTest.hpp"

QString EnvironmentManagerTest::getDatabaseFilePath() const
{
    return "capops.db";
}

quint16 EnvironmentManagerTest::getHttpPort() const
{
    return 8080;
}

quint16 EnvironmentManagerTest::getWebSocketPort() const
{
    return 8081;
}

QString EnvironmentManagerTest::getRedisHost() const
{
    return "redis";
}

QString EnvironmentManagerTest::getRedisPort() const
{
    return "6379";
}

int EnvironmentManagerTest::getProtoBufContractVersion() const
{
    return 1;
}

int EnvironmentManagerTest::getRestJsonContractVersion() const
{
    return 1;
}