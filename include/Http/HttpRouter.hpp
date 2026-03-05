#pragma once

#include <QHttpServer>

class FlightDataController;
class RiskEventController;

class HttpRouter
{
public:
    explicit HttpRouter(QHttpServer& server);

    void registerFlightDataController(FlightDataController& flightDataController);
    void registerRiskEventController(RiskEventController& riskEventController);

private:
    QHttpServer& _server;
};
