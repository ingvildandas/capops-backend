#pragma once

#include <QString>
#include <QtGlobal>

#include "IEnvironmentManager.hpp"

class EnvironmentManagerTest : public IEnvironmentManager
{
public:
    EnvironmentManagerTest() = default;

    QString getDatabaseFilePath() const override;
    quint16 getHttpPort() const override;
    quint16 getWebSocketPort() const override;
    QString getRedisHost() const override;
    QString getRedisPort() const override;
    int getProtoBufContractVersion() const override;
    int getRestJsonContractVersion() const override;
};