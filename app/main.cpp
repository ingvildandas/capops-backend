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

namespace
{
    struct ApplicationContext
    {
        DatabaseConnection conn {"capops.db"};
        
        FlightDataStateManager flightDataStateManager;
        WebSocketSessionManager sessionManager;

        RiskEventRepository riskEventRepository {conn};
        RiskEventService riskEventService {riskEventRepository, flightDataStateManager};

        RiskEventController riskEventController {riskEventService};
        WebSocketController webSocketController {sessionManager};
        
        HttpServer httpServer {8080};
        WebSocketServer wsServer {8081};

        void initialize()
        {  
            qInfo() << "Database connection successful";
            
            httpServer.registerRiskEventController(riskEventController);
            if (!httpServer.start()) throw HttpException("Failed to start HTTP server"); 

            wsServer.registerWebSocketController(webSocketController);
            wsServer.start();
            qInfo() << "WebSocket server listening on port " << wsServer.getPort();
        }
    };
}

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    
    try
    {
        ApplicationContext context;
        context.initialize();
        return app.exec();
    }
    catch(const ApplicationException& e)
    {
        qCritical() << "Application error: " << e.what();
        return -1;
    }
    catch(const std::exception& e)
    {
        qCritical() << "Unexpected error: " << e.what();
        return -1;
    }
    
    return EXIT_FAILURE;
}