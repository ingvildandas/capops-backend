#pragma once

#include <QHttpServer>

class RiskEventController;

class HttpRouter
{
public:
    explicit HttpRouter(QHttpServer& server);

    void registerRiskEventController(RiskEventController& riskEventController);

private:
    QHttpServer& _server;
};
