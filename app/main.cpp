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

#include "Managers/EnvironmentManager.hpp"
#include "Managers/FlightDataStateManager.hpp"
#include "Managers/WebSocketSessionManager.hpp"

#include "Network/HttpServer.hpp"
#include "Network/RedisEventBusReceiver.hpp"
#include "Network/WebSocketServer.hpp"

#include "Repositories/RiskEventRepository.hpp"

#include "Services/MetadataService.hpp"
#include "Services/RiskEventService.hpp"
#include "Services/SectorSummaryService.hpp"
#include "Services/TrackService.hpp"

namespace
{
    struct ApplicationContext
    {
        EnvironmentManager envManager {".env"};
        DatabaseConnection conn 
        {
            envManager.getDatabaseFilePath().toStdString()
        };
        
        FlightDataStateManager flightDataStateManager;
        WebSocketSessionManager sessionManager {envManager};

        RiskEventRepository riskEventRepository {conn};

        MetadataService metadataService;
        RiskEventService riskEventService {riskEventRepository};
        SectorSummaryService sectorSummaryService;
        TrackService trackService;

        RiskEventController riskEventController {riskEventService};
        WebSocketController webSocketController {sessionManager};

        RedisEventBusReceiver redisReceiver 
        {
            envManager.getRedisUri(), 
            sessionManager, 
            flightDataStateManager, 
            metadataService, 
            riskEventService, 
            sectorSummaryService, 
            trackService
        };

        HttpServer httpServer {envManager.getHttpPort()};
        WebSocketServer wsServer {envManager.getWebSocketPort()};

        void initialize()
        {  
            qInfo() << "Database connection successful";
            
            httpServer.registerRiskEventController(riskEventController);
            httpServer.start();
            qInfo() 
                << "HTTP server listening on port " 
                << httpServer.getPort();

            wsServer.registerWebSocketController(webSocketController);
            wsServer.start();
            qInfo() 
                << "WebSocket server listening on port " 
                << wsServer.getPort();
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
    }
    catch(const std::exception& e)
    {
        qCritical() << "Unexpected error: " << e.what();
    }
    
    return EXIT_FAILURE;
}