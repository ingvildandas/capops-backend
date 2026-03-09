#include <QCoreApplication>
#include <QDebug>
#include <QHostAddress>
#include <QHttpServer>
#include <QTcpServer>
#include <QtGlobal>

#include "Database/DatabaseConnection.hpp"
#include "Http/HttpRouter.hpp"
#include "Controllers/RiskEventController.hpp"
#include "Controllers/WebSocketController.hpp"
#include "Managers/FlightDataStateManager.hpp"
#include "Managers/WebSocketSessionManager.hpp"
#include "Repositories/RiskEventRepository.hpp"
#include "Services/RiskEventService.hpp"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    QHttpServer httpServer;

    auto conn = DatabaseConnection("capops.db");
    qDebug() << "Database connection successful";
    
    RiskEventRepository riskEventRepository(conn);
    FlightDataStateManager flightDataStateManager;
    RiskEventService riskEventService(riskEventRepository, flightDataStateManager);
    RiskEventController riskEventController(riskEventService);
    
    HttpRouter router(httpServer);
    router.registerRiskEventController(riskEventController);

    WebSocketSessionManager webSocketSessionManager;
    WebSocketController webSocketController(webSocketSessionManager);

    auto tcpServer = new QTcpServer();
    if (!tcpServer->listen(QHostAddress::Any, 8080))
    {
        delete tcpServer;
        return -1;
    }
    
    return app.exec();
}