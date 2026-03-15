#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QtGlobal>

#include "Controllers/RiskEventController.hpp"
#include "Controllers/WebSocketController.hpp"
#include "Database/DatabaseConnection.hpp"
#include "Exceptions/ApplicationException.hpp"
#include "Exceptions/DatabaseException.hpp"
#include "Exceptions/HttpException.hpp"
#include "Exceptions/RedisEventBusException.hpp"
#include "Exceptions/WebSocketException.hpp"
#include "Managers/FlightDataStateManager.hpp"
#include "Managers/WebSocketSessionManager.hpp"
#include "Network/HttpServer.hpp"
#include "Network/WebSocketServer.hpp"
#include "Repositories/RiskEventRepository.hpp"
#include "Services/RiskEventService.hpp"

int main(int argc, char* argv[])
{
    try
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
        if (!httpServer.start()) throw HttpException("Failed to start HTTP server"); 
        
        WebSocketServer wsServer(8081);
        wsServer.registerWebSocketController(webSocketController);
        if (!wsServer.start()) throw WebSocketException("Failed to start WebSocket server");
    
        return app.exec();
    }
    catch(const ApplicationException& e)
    {
        qDebug() << "Application error: " << e.what();
        return -1;
    }
    catch(const std::exception& e)
    {
        qDebug() << "Unexpected error: " << e.what();
        return -1;
    }
}