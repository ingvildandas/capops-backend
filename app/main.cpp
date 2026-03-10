#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QtGlobal>

#include "Database/DatabaseConnection.hpp"
#include "Controllers/RiskEventController.hpp"
#include "Controllers/WebSocketController.hpp"
#include "Managers/FlightDataStateManager.hpp"
#include "Managers/WebSocketSessionManager.hpp"
#include "Network/HttpServer.hpp"
#include "Network/WebSocketServer.hpp"
#include "Repositories/RiskEventRepository.hpp"
#include "Services/RiskEventService.hpp"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    auto conn = DatabaseConnection("capops.db");
    qDebug() << "Database connection successful";
    
    RiskEventRepository riskEventRepository(conn);
    FlightDataStateManager flightDataStateManager;

    RiskEventService riskEventService(riskEventRepository, flightDataStateManager);
    RiskEventController riskEventController(riskEventService);

    WebSocketSessionManager sessionManager;
    WebSocketController webSocketController(sessionManager);
    
    HttpServer httpServer(8080);
    httpServer.registerRiskEventController(riskEventController);
    if (!httpServer.start()) return -1; 
    
    WebSocketServer wsServer(8081);
    wsServer.registerWebSocketController(webSocketController);
    if (!wsServer.start()) return -1;

    return app.exec();
}