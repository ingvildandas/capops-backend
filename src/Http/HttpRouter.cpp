#include <QHttpServer>

#include "Network/HttpRouter.hpp"
#include "Controllers/RiskEventController.hpp"

HttpRouter::HttpRouter(QHttpServer& server) : _server(server)
{}

void HttpRouter::registerRiskEventController
(
    RiskEventController& riskEventController
)
{}

