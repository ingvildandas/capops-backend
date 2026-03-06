#include <QHttpServer>

#include "Http/HttpRouter.hpp"
#include "Controllers/RiskEventController.hpp"

HttpRouter::HttpRouter(QHttpServer& server) : _server(server)
{}

void HttpRouter::registerRiskEventController
(
    RiskEventController& riskEventController
)
{}

